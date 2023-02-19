#ifndef CALCULATOR_CREATOR_BY_FILE_HPP
#define CALCULATOR_CREATOR_BY_FILE_HPP
#include "command.hpp"
#include "parser.hpp"

class CreatorByFile{
public:
    static Command get(const std::filesystem::path& filename);
};
#endif //CALCULATOR_CREATOR_BY_FILE_HPP
