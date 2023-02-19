#ifndef COMMAND_TEXT_EDITOR_HPP
#define COMMAND_TEXT_EDITOR_HPP
#include <utility>

#include "command_dto.hpp"
#include "factory.hpp"
#include "command_stack.hpp"
#include "parser.hpp"
#include "service_command_factory.hpp"

class TextEditor final{
    std::shared_ptr<TextProcessor> text_processor;
    CommandStack command_stack;

public:
    TextEditor(std::string string_to_edit) :
        text_processor(std::make_shared<TextProcessor>(std::move(string_to_edit))), command_stack(text_processor){};

    void process(std::unique_ptr<Command> text_cmd);

    void process(std::unique_ptr<ServiceCommand> service_cmd);

    std::string get();
};
#endif //COMMAND_TEXT_EDITOR_HPP
