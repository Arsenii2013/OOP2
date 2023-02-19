#ifndef CALCULATOR_SETTINGS_HPP
#define CALCULATOR_SETTINGS_HPP

#include <filesystem>
#include <utility>
class Settings{
    std::size_t n_files{};
    std::filesystem::path root{};
    std::filesystem::path out_file{"out.dat"};
    std::filesystem::path log_file{"log.log"};
    bool log{true};
public:
    Settings() = default;
    Settings(size_t nFiles, std::filesystem::path root, std::filesystem::path outFile,
             std::filesystem::path logFile, bool log) : n_files(nFiles), root(std::move(root)), out_file(std::move(outFile)),
                                                               log_file(std::move(logFile)), log(log) {}

    [[nodiscard]] size_t get_n_files() const {
        return n_files;
    }

    [[nodiscard]] const std::filesystem::path &get_root() const {
        return root;
    }

    [[nodiscard]] const std::filesystem::path &get_out_file() const {
        return out_file;
    }

    [[nodiscard]] const std::filesystem::path &get_log_file() const {
        return log_file;
    }

    [[nodiscard]] bool get_log() const {
        return log;
    }

    void set_n_files(size_t nFiles) {
        n_files = nFiles;
    }

    void set_root(const std::filesystem::path &_root) {
        Settings::root = _root;
    }

    void set_out_file(const std::filesystem::path &outFile) {
        out_file = outFile;
    }

    void set_log_file(const std::filesystem::path &logFile) {
        log_file = logFile;
    }

    void set_fog(bool _log) {
        Settings::log = _log;
    }
};

#endif //CALCULATOR_SETTINGS_HPP
