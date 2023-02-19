#ifndef CALCULATOR_SETTINGS_PARSER_HPP
#define CALCULATOR_SETTINGS_PARSER_HPP
#include <sstream>
#include "settings.hpp"

class SettingsParser{
    std::istream& is;

public:
    explicit SettingsParser( std::istream &is) : is(is) {}

    Settings parse();
};

[[nodiscard]] std::size_t count_files();

#endif //CALCULATOR_SETTINGS_PARSER_HPP
