//
// Created by sescer on 20.12.22.
//

#ifndef COMMAND_REDO_HPP
#define COMMAND_REDO_HPP
#include "service_command.hpp"
class Redo : public ServiceCommand{
public:
    Redo();

    void execute(CommandStack & stack) override;
};
#endif //COMMAND_REDO_HPP
