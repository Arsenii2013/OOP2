#include "text_editor.hpp"

void TextEditor::process(std::unique_ptr<Command> text_cmd) {
    command_stack.add_and_execute(std::move(text_cmd));
}

void TextEditor::process(std::unique_ptr<ServiceCommand> service_cmd) {
    service_cmd->execute(command_stack);
}

std::string TextEditor::get() {
    return text_processor->get();
}
