#include "factory.hpp"
#include "command_names.hpp"

class CompareByName{
public:
    bool operator()(const CommandDTO& a, const CommandDTO& b) const{
        return a.get_name() < b.get_name();
    }
};

static std::map<CommandDTO, std::function<std::unique_ptr<Command> (const CommandDTO&)>, CompareByName> creators
        {{{CommandDTO{CommandNames::InsertName},
           [](const CommandDTO& info){return std::make_unique<Insert>(info.get_pos(), info.get_str());}},
          {CommandDTO{CommandNames::DeleteName},
           [](const CommandDTO& info){return std::make_unique<Delete>(info.get_interval());}},
          {CommandDTO{CommandNames::CopyName},
           [](const CommandDTO& info){return std::make_unique<Copy>(info.get_interval());}},
          {CommandDTO{CommandNames::PasteName},
           [](const CommandDTO& info){return std::make_unique<Paste>(info.get_pos());}}}};

std::unique_ptr<Command> TextCommandFactory::create(const CommandDTO &cmd) {
    return creators[cmd](cmd);
}
