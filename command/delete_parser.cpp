#include "delete_parser.hpp"

CommandDTO DeleteParser::operator()(std::istream &is) {
    std::size_t start, stop;
    is >> start >> stop;
    return {std::string(CommandNames::DeleteName), {start, stop}};
}
