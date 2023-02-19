#include "gtest/gtest.h"
#include <chrono>
#include <random>
#include <algorithm>

#include "command.hpp"
#include "logger.hpp"
#include "parser.hpp"
#include "settings.hpp"
#include "sequential_calculator.hpp"
#include "parallel_calculator.hpp"
#include "settings_parser.hpp"

double sum(double a, double b){
    return a + b;
}

TEST(Command, Command){
    {
        Command test([](double, double){return 3.;}, "test_cmd", 1, 2);
        EXPECT_DOUBLE_EQ(3., test.execute());
        EXPECT_EQ("command: test_cmd with argument: 1.000000, 2.000000", test.get_info());
    }
    {
        Command test(sum, "test_cmd", 1., 2.123123);
        EXPECT_DOUBLE_EQ(3.123123, test.execute());
        EXPECT_EQ("command: test_cmd with argument: 1.000000, 2.123123", test.get_info());
    }
}

TEST(Parser, KnownCommands){
    {
       Parser p{"add 1 0.5"};
       auto cmd = p.get();

        EXPECT_DOUBLE_EQ(1.5, cmd.execute());
        EXPECT_EQ("command: add with argument: 1.000000, 0.500000", cmd.get_info());
    }
    {
        Parser p{"mult 1 0.5"};
        auto cmd = p.get();

        EXPECT_DOUBLE_EQ(0.5, cmd.execute());
        EXPECT_EQ("command: mult with argument: 1.000000, 0.500000", cmd.get_info());
    }
    {
        Parser p{"add_sq 1 0.5"};
        auto cmd = p.get();

        EXPECT_DOUBLE_EQ(1.25, cmd.execute());
        EXPECT_EQ("command: add_sq with argument: 1.000000, 0.500000", cmd.get_info());
    }
    {
        Parser p{"sq_add 1 0.5"};
        auto cmd = p.get();

        EXPECT_DOUBLE_EQ(2.25, cmd.execute());
        EXPECT_EQ("command: sq_add with argument: 1.000000, 0.500000", cmd.get_info());
    }
    {
        Parser p{"sub 1 0.5"};
        auto cmd = p.get();

        EXPECT_DOUBLE_EQ(0.5, cmd.execute());
        EXPECT_EQ("command: sub with argument: 1.000000, 0.500000", cmd.get_info());
    }
    {
        Parser p{"div 1 0.5"};
        auto cmd = p.get();

        EXPECT_DOUBLE_EQ(2, cmd.execute());
        EXPECT_EQ("command: div with argument: 1.000000, 0.500000", cmd.get_info());
    }
}

TEST(Parser, UnknownCommands){
    {
        Parser p{"arror 1 0.5"};
        //EXPECT_ANY_THROW(p.get());
    }
    {
        Parser p{"sum t 0.5"};
        //EXPECT_ANY_THROW(p.get());
    }
    {
        Parser p{"sum 1 0.5 asdasd"};
        //EXPECT_ANY_THROW(p.get());
    }
}

TEST(Settings, Empty){
    {
        std::istringstream iss{};
        std::cout << "there" << std::endl;
        SettingsParser p(iss);
        std::cout << "there" << std::endl;
        Settings settings = p.parse();
        std::cout << "there" << std::endl;
        EXPECT_EQ(std::filesystem::path{}, settings.get_root());
        std::cout << "there" << std::endl;
        EXPECT_EQ(std::filesystem::path{"out.dat"}, settings.get_out_file());
        EXPECT_EQ(std::filesystem::path{"log.log"}, settings.get_log_file());
        EXPECT_TRUE(settings.get_log());
        std::cout << "there" << std::endl;
    }
}

TEST(Settings, Settings){
    {
        std::istringstream iss{"root ./\n"
                                   "log false\n"
                                   "log_file first.log\n"
                                    "out_file first.dat\n"};
        SettingsParser p(iss);
        Settings settings = p.parse();
        EXPECT_EQ(std::filesystem::path{"./"}, settings.get_root());
        EXPECT_EQ(std::filesystem::path{"first.log"}, settings.get_log_file());
        EXPECT_EQ(std::filesystem::path{"first.dat"}, settings.get_out_file());
        EXPECT_FALSE(settings.get_log());
    }
    {
        std::istringstream iss{"root ./\n"
                                   "log false\n"
                                   "log_file first.log\n"
                                   "out_file first.dat\n"
                                   "out_file second.dat\n"
                                   "log_file second.log\n"
                                   "log 1\n"
                                   "root ~\n"};
        SettingsParser p(iss);
        Settings settings = p.parse();
        EXPECT_EQ(std::filesystem::path{"~"}, settings.get_root());
        EXPECT_EQ(std::filesystem::path{"second.log"}, settings.get_log_file());
        EXPECT_EQ(std::filesystem::path{"second.dat"}, settings.get_out_file());
        EXPECT_TRUE(settings.get_log());
    }
}

TEST(Settings, Wrong){
    {
        std::istringstream iss{"root ./\n"
                               "log false\n"
                               "log_file first.log\n"
                               "out_file first.dat\n"
                               "asfasfafaeef asd\n"
                               ""};
        SettingsParser p(iss);
        EXPECT_ANY_THROW(p.parse());
    }
    {
        std::istringstream iss{""};
        SettingsParser p(iss);
        EXPECT_NO_THROW(p.parse());
    }
    {
        std::istringstream iss{"log\n"};
        SettingsParser p(iss);
        //EXPECT_ANY_THROW(p.parse());
    }
}

class CommandsGenerator {
    std::size_t n_files;
    double sum=0.;
    std::map<std::string, std::function<double (double, double)>> commands{
            {"add", [](double a , double b){return a + b; }},
            {"mult", [](double a , double b){return a * b; }},
            {"add_sq", [](double a , double b){return a * a + b * b; }},
            {"sq_add", [](double a , double b){return (a + b) * (a + b); }},
            {"sub", [](double a , double b){return a - b; }},
            {"div", [](double a , double b){return a / b; }},
    };

    std::size_t generate_commands() {
        auto gen = std::mt19937{std::random_device{}()};
        n_files = std::uniform_int_distribution<std::size_t>{1000, 10000}(gen);

        for(std::size_t i = 1; i <= n_files; i++){
            std::pair<std::string, std::function<double (double, double)>> cmd;
            std::sample(commands.begin(), commands.end(), &cmd, 1, gen);
            double arg1 = std::uniform_real_distribution<double>{-10, 10}(gen);
            double arg2 = std::uniform_real_distribution<double>{-10, 10}(gen);

            sum += cmd.second(arg1, arg2);
            std::ofstream cmd_file("in_" + std::to_string(i) + ".dat");
            cmd_file << cmd.first << " " << arg1 << " " << arg2 << std::endl;
        }
        return n_files;
    }

    void delete_commands(){
        for(std::size_t i = 1; i <= n_files; i++){
            std::filesystem::remove("in_" + std::to_string(i) + ".dat");
        }
    }

public:
    CommandsGenerator(){
        generate_commands();
    }

    double get_sum() const {
        return sum;
    }

    std::size_t get_n_files() const {
        return n_files;
    }

    ~CommandsGenerator(){
        delete_commands();
    }
};

TEST(Calculators, Sequential){
    CommandsGenerator gen;

    SequentialCalculator sh(true, gen.get_n_files());

    EXPECT_NEAR(gen.get_sum(), sh.get_sum(), abs(gen.get_sum() / pow(10, 5)));
}

TEST(Calculators, Parallel){
    CommandsGenerator gen;

    ParallelCalculator sh(true, 1, gen.get_n_files());

    EXPECT_NEAR(gen.get_sum(), sh.get_sum(), abs(gen.get_sum() / pow(10, 5)));
}

template<class Calculator, class ...Args>
std::chrono::duration<long, std::ratio<1, 1000000000>> meashure_time(const CommandsGenerator &gen, Args...args){
    auto begin = std::chrono::steady_clock::now();
    Calculator sh{args...};
    EXPECT_NEAR(gen.get_sum(), sh.get_sum(), abs(gen.get_sum() / pow(10, 5)));
    auto end = std::chrono::steady_clock::now();

    return end - begin;
}

TEST(SpeedTest, WithLog){
    CommandsGenerator gen;

    auto parallel = meashure_time<ParallelCalculator>(gen, true, std::size_t(2), gen.get_n_files());

    auto line = meashure_time<SequentialCalculator>(gen, true, gen.get_n_files());

    std::cout << "Parallel " << (double) line.count() / parallel.count() << " times faster than line. With log" << std::endl;
}

TEST(SpeedTest, NoLog){
    CommandsGenerator gen;

    auto parallel = meashure_time<ParallelCalculator>(gen, false, std::size_t(4), gen.get_n_files());

    auto line = meashure_time<SequentialCalculator>(gen, false, gen.get_n_files());

    std::cout << "Parallel " << (double) line.count() / parallel.count() << " times faster than line. Without log" << std::endl;
}

TEST(SpeedTest, DifThreadN) {
    CommandsGenerator gen;

    auto reference = meashure_time<SequentialCalculator>(gen, false, gen.get_n_files());

    std::vector<std::chrono::duration<long, std::ratio<1, 1000000000>>> intervals;
    for (std::size_t i = 1; i < 8; i++) {
        auto elapsed = meashure_time<ParallelCalculator>(gen, false, i, gen.get_n_files());

        intervals.push_back(elapsed);
    }

    std::cout << "Ratio betveen shedulers with different thread number(0-7) ";
    for(const auto& interval: intervals) {
        std::cout << (double ) reference.count() / interval.count() << " ";
    }
    std::cout << std::endl;
}




