//
// Created by sescer on 27.11.22.
//

#ifndef COMMAND_INSERT_HPP
#define COMMAND_INSERT_HPP
#include <utility>

#include "command.hpp"

class Insert: public Command{
private:
    std::size_t pos;
    std::string str;

public:
    Insert( size_t pos, std::string str);

    void redo(TextProcessor &processor) override;

    void undo(TextProcessor &processor) override;
};

#endif //COMMAND_INSERT_HPP
