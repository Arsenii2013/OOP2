#ifndef COMMAND_PASTE_PARSER_HPP
#define COMMAND_PASTE_PARSER_HPP
#include "command_dto.hpp"
#include "command_names.hpp"

class PasteParser{
public:
    CommandDTO operator()(std::istream& is);
};


#endif //COMMAND_PASTE_PARSER_HPP
