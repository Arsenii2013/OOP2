//
// Created by sescer on 23.11.22.
//

#ifndef COMMAND_COMMAND_HPP
#define COMMAND_COMMAND_HPP

#include "clipboard.hpp"
#include <iostream>
#include <memory>
#include <utility>
#include "text_processor.hpp"

class Command{
protected:
    std::string name;
public:

    Command() = default;

    explicit Command(std::string name) : name(std::move(name)) {}

    [[nodiscard]] const std::string & get_name() const{
        return name;
    }

    virtual void redo(TextProcessor &processor) {};
    virtual void undo(TextProcessor &processor) {};

    virtual ~Command() = default;
};

#endif //COMMAND_COMMAND_HPP
