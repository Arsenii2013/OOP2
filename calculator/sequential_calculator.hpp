//
// Created by sescer on 17.12.22.
//

#ifndef CALCULATOR_SEQUENTIAL_CALCULATOR_HPP
#define CALCULATOR_SEQUENTIAL_CALCULATOR_HPP
#include <string>
#include <fstream>
#include <filesystem>

class SequentialCalculator final{
    double sum{0.};
    bool need_log{true};
    std::size_t n_files{0};

    void process_file(const std::filesystem::path& file);
public:
    SequentialCalculator(bool needLog, size_t nFiles);

    [[nodiscard]] double get_sum() const;
};
#endif //CALCULATOR_SEQUENTIAL_CALCULATOR_HPP
