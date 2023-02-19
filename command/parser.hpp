//
// Created by sescer on 04.12.22.
//

#ifndef COMMAND_PARSER_HPP
#define COMMAND_PARSER_HPP
#include "command_dto.hpp"
#include "command.hpp"
#include "insert.hpp"
#include "delete.hpp"
#include "copy.hpp"
#include "paste.hpp"
#include "text_processor.hpp"
#include <string>
#include <sstream>
#include <utility>
#include <functional>
#include <map>

class Parser{
    std::istream& is;

public:
    explicit Parser(std::istream &is) : is(is) {}

    [[nodiscard]] bool can_parse() const;

    [[nodiscard]] CommandDTO parse();
};

#endif //COMMAND_PARSER_HPP
