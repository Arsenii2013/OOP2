#ifndef CALCULATOR_PARALLEL_CALCULATOR_HPP
#define CALCULATOR_PARALLEL_CALCULATOR_HPP
#include <string>
#include <fstream>
#include <filesystem>
#include <atomic>
#include <queue>
#include <thread>
#include <future>

class ParallelCalculator final{
private:
    bool need_log{true};
    std::size_t n_threads{0U};
    std::size_t n_files{0U};


    double sum{0.};
    std::vector<std::future<double>> worker_threads{};

    [[nodiscard]] double process_interval(std::size_t start, std::size_t stop) const;

public:
    static constexpr std::size_t min_files_per_thread = 100;

    ParallelCalculator(bool needLog, size_t nThreads, size_t nFiles);

    double get_sum();
};

#endif //CALCULATOR_PARALLEL_CALCULATOR_HPP
