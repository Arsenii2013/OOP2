#include <iostream>
#include "logger.hpp"
#include "command.hpp"
#include "settings.hpp"

#include <filesystem>
#include "parallel_calculator.hpp"
#include "settings_parser.hpp"

int main(int argc, char** argv) {
    if(argc != 2){
        std::cout << "Usage: " << argv[0] << " setiings_file" << std::endl;
    }

    std::ifstream settings_file(argv[1]);

    SettingsParser settings_parser(settings_file);
    auto settings = settings_parser.parse();

    std::filesystem::current_path(settings.get_root());
    Logger::get_instance().set_file(settings.get_log_file());

    if(settings.get_n_files() == 0){
        settings.set_n_files(count_files());
    }

    ParallelCalculator sh(settings.get_log(), 2, settings.get_n_files());

    std::ofstream out_file(settings.get_out_file());
    out_file << sh.get_sum() << std::endl;

    return 0;
}
