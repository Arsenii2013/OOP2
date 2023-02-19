//
// Created by sescer on 20.12.22.
//

#include "undo.hpp"
#include "command_names.hpp"

void Undo::execute(CommandStack &stack) {
    stack.undo();
}

Undo::Undo() : ServiceCommand(CommandNames::UndoName) {}
