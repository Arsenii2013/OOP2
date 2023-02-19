#ifndef COMMAND_INSERT_PARSER_HPP
#define COMMAND_INSERT_PARSER_HPP
#include "command_dto.hpp"
#include "command_names.hpp"

class InsertParser{
public:
    CommandDTO operator()(std::istream& is);
};

#endif //COMMAND_INSERT_PARSER_HPP
