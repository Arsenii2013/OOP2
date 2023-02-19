#include "insert_parser.hpp"

CommandDTO InsertParser::operator()(std::istream &is) {
    std::size_t pos;
    std::string insert_string;
    is >> pos >> insert_string;
    return {std::string(CommandNames::InsertName), pos, insert_string};
}
