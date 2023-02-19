//
// Created by sescer on 09.12.22.
//

#ifndef CALCULATOR_PARSER_HPP
#define CALCULATOR_PARSER_HPP
#include <functional>
#include <istream>
#include <map>
#include <fstream>
#include <sstream>
#include <utility>

#include "command.hpp"

class Parser{
    std::string string_to_parse{};
public:
    explicit Parser(std::string stringToParse) : string_to_parse(std::move(stringToParse)) {}

    [[maybe_unused]] Command get();
};

#endif //CALCULATOR_PARSER_HPP
