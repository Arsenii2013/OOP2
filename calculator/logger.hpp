//
// Created by sescer on 08.12.22.
//

#ifndef CALCULATOR_LOGGER_HPP
#define CALCULATOR_LOGGER_HPP

#include <utility>
#include <chrono>
#include <iostream>
#include <filesystem>
#include <syncstream>
#include <fstream>

class Logger final{
    std::ofstream log_file;
    Logger() = default;
public:
    Logger(const Logger&) = delete;
    Logger operator=(const Logger&) = delete;

    static Logger& get_instance();

    void set_file(const std::filesystem::path& file);

    void log(const std::string& message);
};

#endif //CALCULATOR_LOGGER_HPP
