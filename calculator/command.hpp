//
// Created by sescer on 08.12.22.
//

#ifndef CALCULATOR_COMMAND_HPP
#define CALCULATOR_COMMAND_HPP
#include <functional>
#include <istream>
#include <map>
#include <fstream>
#include <sstream>
#include <utility>

#include "logger.hpp"

class Command{
    std::function<double (double, double)> math_cmd;
    std::string name;
    double arg1;
    double arg2;
public:
    Command(std::function<double(double, double)> mathCmd, std::string name, double arg1, double arg2);

    [[nodiscard]] double execute() const;

    std::string get_info();
};

#endif //CALCULATOR_COMMAND_HPP
