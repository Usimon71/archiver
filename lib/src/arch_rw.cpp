#include "arch_rw.h"

template <size_t K>
uint64_t ArchWriter<K>::GetFileSize(std::filesystem::path path) {
    uint64_t msg_size = ((1 << K) - K - 1) / 8;
    std::filesystem::path result_path(base_dir_.string() + path.string());
    uint64_t num_of_blocks = (static_cast<uint64_t>(std::ifstream(result_path, std::ios::ate).tellg()) + msg_size - 1) / msg_size;
    uint64_t ans = num_of_blocks * (msg_size + ((K + 1) / 8));
    
    return ans;
}

template <size_t K>
void ArchWriter<K>::Write(bool app, bool single_mistake, bool double_mistake) {
    FileReader file_in(in_path_, base_dir_);
    FileWriter file_out(out_path_, base_dir_, app);
    
    uint64_t file_sz = GetFileSize(in_path_);
    std::cout << "file size: " << file_sz << '\n';
    file_out.WriteMeta(in_path_, file_sz);
    HamArc::HammingCode<K> ham_code(file_in, file_out);
    if (single_mistake) {
        ham_code.single_mistake = true;
    } else if (double_mistake) {
        ham_code.double_mistake = true;
    }
    while (ham_code.CodeMsg());
}

template class ArchWriter<7>;
template class ArchWriter<15>;

template <size_t K>
uint64_t ArchReader<K>::SearchFile(FileReader& file, std::filesystem::path& path_out) {
    std::filesystem::path path_comp;
    uint64_t file_size;
    while(file.ReadMeta(path_comp, file_size)){
        std::cout << "file name: " << path_comp << ", file_size: " << file_size << '\n';
        if (path_comp == path_out) {
            return file_size;
        }
        
        file.OffsetPtr(file_size);
    }
    std::cerr << "File not found!\n";
    
    return 0;
}

template <size_t K>
void ArchReader<K>::Read() {
    FileReader file_in(in_path_, base_dir_);
    FileWriter file_out(out_path_, base_dir_, false);
    uint64_t code_size = SearchFile(file_in, out_path_);
    HamArc::HammingCode<K> ham_code(file_in, file_out);
    size_t block_size = (1 << K) / 8;
    uint64_t num_of_blocks = code_size / block_size;
    for (size_t i = 0; i != num_of_blocks - 1; ++i) {
        ham_code.DeCodeMsg();
    }
    ham_code.DeCodeMsg(true);
}

template <size_t K>
void ArchReader<K>::ReadAll() {
    FileReader file_in(in_path_, base_dir_);
    std::filesystem::path path;
    uint64_t file_size;
    size_t block_size = (1 << K) / 8;
    while (file_in.ReadMeta(path, file_size)) {
        uint64_t num_of_blocks = file_size / block_size;
        FileWriter file_out(path, base_dir_, false);
        HamArc::HammingCode<K> ham_code(file_in, file_out);
        for (size_t i = 0; i != num_of_blocks; ++i) {
            ham_code.DeCodeMsg();
        }
    }
}
template <size_t K>
void ArchReader<K>::ListFiles() {
    FileReader file_in(in_path_, base_dir_);
    std::filesystem::path path;
    uint64_t file_size;
    uint64_t count = 1;
    std::cout << "Files in archive " << in_path_ << ":\n";
    while (file_in.ReadMeta(path, file_size)) {
        std::cout << count << ". " << path << '\n';
        file_in.OffsetPtr(file_size);
        ++count;
    }
}

template <size_t K>
void ArchReader<K>::CopyFile() {
    FileReader file_in(in_path_, base_dir_);
    FileWriter file_out(out_path_, base_dir_, true);
    char byte;
    while(!file_in.EndOfFile()) {
        byte = file_in.GetByte();
        file_out.PutByte(byte);
    }
}
template <size_t K>
void ArchReader<K>::RemoveExcept(std::filesystem::path to_del) {
    FileReader file_r(in_path_, base_dir_);
    FileWriter file_tmp_w("temp.haf", base_dir_);
    std::cout << to_del << " deleted\n";
    std::filesystem::path path;
    uint64_t file_size;
    while (file_r.ReadMeta(path, file_size)) {
        if (path == to_del) {
            file_r.OffsetPtr(file_size);
        } else {
            file_tmp_w.WriteMeta(path, file_size);
            char byte;
            for (size_t i = 0; i != file_size; ++i) {
                byte = file_r.GetByte();
                file_tmp_w.PutByte(byte);
            }
        }
    }
}

template <size_t K>
void ArchReader<K>::WriteExcept() {
    FileReader file_tmp_r("temp.haf", base_dir_);
    FileWriter file_w(in_path_, base_dir_);
    char byte;
    while(!file_tmp_r.EndOfFile()) {
        byte = file_tmp_r.GetByte();
        file_w.PutByte(byte);
    }
    file_tmp_r.DeleteMe("temp.haf");
}

template <size_t K>
void ArchReader<K>::Delete(std::filesystem::path to_del) {
    RemoveExcept(to_del);
    WriteExcept();
}

template class ArchReader<7>;
template class ArchReader<15>;