//
// Created by sescer on 21.12.22.
//
#include "command.hpp"

Command::Command(std::function<double(double, double)> mathCmd, std::string name, double arg1, double arg2)
        : math_cmd(std::move(mathCmd)), name(std::move(name)), arg1(arg1), arg2(arg2) {}

double Command::execute() const {
    return math_cmd(arg1, arg2);
}

std::string Command::get_info() {
    return "command: " + name + " with argument: " + std::to_string(arg1) + ", " + std::to_string(arg2);
}
