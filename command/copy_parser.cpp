#include "copy_parser.hpp"

CommandDTO CopyParser::operator()(std::istream &is) {
    std::size_t start, stop;
    is >> start >> stop;
    return {std::string(CommandNames::CopyName), {start, stop}};
}
