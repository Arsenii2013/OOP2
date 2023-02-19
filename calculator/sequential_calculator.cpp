#include "sequential_calculator.hpp"

#include "parser.hpp"
#include "logger.hpp"
#include "command.hpp"
#include "creator_by_file.hpp"

void SequentialCalculator::process_file(const std::filesystem::path &file) {
    Command cmd = CreatorByFile::get(file);

    sum += cmd.execute();

    if(need_log){
        Logger::get_instance().log(cmd.get_info());
    }
}

SequentialCalculator::SequentialCalculator(bool needLog, size_t nFiles) : need_log(needLog), n_files(nFiles) {
    for(std::size_t i = 1; i <= n_files; i++){
        process_file("in_" + std::to_string(i) + ".dat");
    }
}

double SequentialCalculator::get_sum() const {
    return sum;
}
