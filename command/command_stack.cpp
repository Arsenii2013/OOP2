#include "command_stack.hpp"

void CommandStack::add_and_execute(std::unique_ptr<Command> cmd) {
    redoed.push(std::move(cmd));
    redoed.top()->redo(*processor);
}

void CommandStack::undo() {
    undoed.push(std::move(redoed.top()));
    redoed.pop();
    undoed.top()->undo(*processor);
}

void CommandStack::redo() {
    redoed.push(std::move(undoed.top()));
    undoed.pop();
    redoed.top()->redo(*processor);
}
