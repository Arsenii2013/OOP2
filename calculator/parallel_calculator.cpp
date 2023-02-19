#include "parallel_calculator.hpp"
#include "parser.hpp"
#include "logger.hpp"
#include "command.hpp"
#include "creator_by_file.hpp"

#include <algorithm>

double ParallelCalculator::process_interval(std::size_t start, std::size_t stop) const {
    if(start < 1U || start > stop){
        throw std::invalid_argument("wrong interval");
    }
    double _sum = 0.;
    std::size_t curr = start;
    for(; curr < stop; curr++){
        Command cmd = CreatorByFile::get("in_" + std::to_string(curr) + ".dat");

        _sum += cmd.execute();

        if(need_log){
            Logger::get_instance().log(cmd.get_info());
        }
    }
    return _sum;
}

ParallelCalculator::ParallelCalculator(bool needLog, size_t nThreads, size_t nFiles) : need_log(needLog), n_threads(nThreads),
                                                                                       n_files(nFiles) {
    n_threads = std::min(n_threads, size_t{std::thread::hardware_concurrency()});
    n_threads = std::min(n_threads, n_files / min_files_per_thread);

    std::size_t files_per_thread = n_files / n_threads;
    std::size_t start_pos = 1U;
    for(std::size_t i = 0U; i < n_threads - 1U; i++){
        worker_threads.push_back(std::async(//std::launch::async,
                                            &ParallelCalculator::process_interval,
                                            this, start_pos, start_pos + files_per_thread));
        start_pos += files_per_thread;
    }
    worker_threads.push_back(std::async(//std::launch::async,
                                        &ParallelCalculator::process_interval,
                                        this, start_pos, start_pos + files_per_thread + n_files % n_threads));
}

double ParallelCalculator::get_sum() {
    for(auto &thread : worker_threads){
        sum += thread.get();
    }

    return sum;
}
