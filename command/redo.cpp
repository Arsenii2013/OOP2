#include "redo.hpp"
#include "command_names.hpp"

void Redo::execute(CommandStack &stack) {
    stack.redo();
}

Redo::Redo() : ServiceCommand(CommandNames::RedoName) {}
