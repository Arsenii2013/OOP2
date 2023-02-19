#ifndef COMMAND_DELETE_PARSER_HPP
#define COMMAND_DELETE_PARSER_HPP
#include "command_dto.hpp"
#include "command_names.hpp"

class DeleteParser{
public:
    CommandDTO operator()(std::istream& is);
};
#endif //COMMAND_DELETE_PARSER_HPP
