#include "parser.hpp"
#include "command_names.hpp"
#include "copy_parser.hpp"
#include "paste_parser.hpp"
#include "insert_parser.hpp"
#include "delete_parser.hpp"

std::map<std::string, std::function<CommandDTO (std::istream&)>> readers{{CommandNames::CopyName, CopyParser()},
                                                                         {CommandNames::PasteName, PasteParser()},
                                                                         {CommandNames::InsertName, InsertParser()},
                                                                         {CommandNames::DeleteName, DeleteParser()},
                                                                         {CommandNames::UndoName, [](std::istream&){return CommandDTO{std::string(CommandNames::UndoName)};}},
                                                                         {CommandNames::RedoName, [](std::istream&){return CommandDTO{std::string(CommandNames::RedoName)};}}};

CommandDTO Parser::parse() {
    std::string string_to_parse;
    if(!getline(is, string_to_parse)){
        return {};
    }
    std::istringstream iss(string_to_parse);

    std::string cmd_name;

    iss >> cmd_name;

    return readers[cmd_name](iss);
}

bool Parser::can_parse() const {
    return !is.eof();
}
