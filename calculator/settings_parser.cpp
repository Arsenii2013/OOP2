#include "settings_parser.hpp"

Settings SettingsParser::parse() {
    Settings res;
    std::string line;
    while (getline(is, line)){
        std::istringstream iss{line};
        std::string param_type;
        try {
            iss >> param_type;
            if (param_type == "root") {
                std::filesystem::path root;
                iss >> root;
                res.set_root(root);
            } else if (param_type == "log") {
                bool log;
                iss >> log;
                res.set_fog(log);
            } else if (param_type == "log_file") {
                std::filesystem::path log_file;
                iss >> log_file;
                res.set_log_file(log_file);
            } else if (param_type == "out_file") {
                std::filesystem::path out_file;
                iss >> out_file;
                res.set_out_file(out_file);
            } else if (param_type == "n_files") {
                std::size_t n_files;
                iss >> n_files;
                res.set_n_files(n_files);
            }else{
                throw std::runtime_error("parse settings error");
            }
        }catch(...){
            throw std::runtime_error("parse settings error");
        }
    }
    return res;
}

//если может быть пропущен номер во входных данных
/*std::size_t count_files1() {
    std::size_t cnt = 1;
    for(; std::filesystem::exists("in_" + std::to_string(cnt) + ".dat"); cnt ++){}
    return cnt;
}*/

//если строго последовательность чисел
std::size_t binary_search(std::size_t low, std::size_t high) {
    if (high >= low) {
        std::size_t mid = low + (high - low) / 2;

        if (!std::filesystem::exists("in_" + std::to_string(mid) + ".dat") &&
            std::filesystem::exists("in_" + std::to_string(mid - 1) + ".dat")) {
            return mid;
        }

        if (!std::filesystem::exists("in_" + std::to_string(mid) + ".dat")) {
            return binary_search(low, mid - 1);
        }
        return binary_search( mid + 1, high);
    }

    return 0;
}

std::size_t count_files() {
    return binary_search(1, std::distance(std::filesystem::directory_iterator{std::filesystem::current_path()},
                                          std::filesystem::directory_iterator{}));
}
