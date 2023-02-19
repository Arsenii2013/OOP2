#ifndef COMMAND_COPY_PARSER_HPP
#define COMMAND_COPY_PARSER_HPP
#include "command_dto.hpp"
#include "command_names.hpp"

class CopyParser{
public:
    CommandDTO operator()(std::istream& is);
};
#endif //COMMAND_COPY_PARSER_HPP
