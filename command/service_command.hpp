//
// Created by sescer on 04.12.22.
//

#ifndef COMMAND_SERVICE_COMMAND_HPP
#define COMMAND_SERVICE_COMMAND_HPP
#include <string>

#include "command_dto.hpp"
#include "command.hpp"
#include "command_stack.hpp"

class ServiceCommand{
protected:
    std::string name;
public:
    ServiceCommand() = default;

    explicit ServiceCommand(std::string name) : name(std::move(name)) {}

    [[nodiscard]] const std::string &get_name() const {
        return name;
    }

    virtual void execute(CommandStack &) {};

    virtual ~ServiceCommand() = default;
};

#endif //COMMAND_SERVICE_COMMAND_HPP
