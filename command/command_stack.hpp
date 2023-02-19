#ifndef COMMAND_COMMAND_STACK_HPP
#define COMMAND_COMMAND_STACK_HPP
#include <stack>
#include <iostream>
#include <utility>

#include "command.hpp"

class CommandStack{
    std::shared_ptr<TextProcessor> processor;
    
    std::stack<std::unique_ptr<Command>> redoed;
    std::stack<std::unique_ptr<Command>> undoed;

public:

    explicit CommandStack(std::shared_ptr<TextProcessor> processor) : processor(std::move(processor)) {}

    void add_and_execute(std::unique_ptr<Command> cmd);

    void undo();

    void redo();
};

#endif //COMMAND_COMMAND_STACK_HPP
