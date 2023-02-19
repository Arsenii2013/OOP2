//
// Created by sescer on 20.12.22.
//

#ifndef COMMAND_UNDO_HPP
#define COMMAND_UNDO_HPP
#include "service_command.hpp"

class Undo : public ServiceCommand{
public:
    Undo();

    void execute(CommandStack & stack) override;
};


#endif //COMMAND_UNDO_HPP
