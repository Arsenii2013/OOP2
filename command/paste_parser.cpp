#include "paste_parser.hpp"

CommandDTO PasteParser::operator()(std::istream &is) {
    std::size_t pos;
    is >> pos;
    return {std::string(CommandNames::PasteName), pos};
}
