#include "logger.hpp"

Logger &Logger::get_instance() {
    static Logger logger;
    return logger;
}

void Logger::set_file(const std::filesystem::path &file) {
    log_file = std::ofstream(file);
}

void Logger::log(const std::string &message) {
    std::osyncstream{log_file} << message << std::chrono::system_clock::now().time_since_epoch();
}
