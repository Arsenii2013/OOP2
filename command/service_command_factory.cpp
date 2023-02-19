#include "service_command_factory.hpp"

class CompareByName{
public:
    bool operator()(const CommandDTO& a, const CommandDTO& b) const{
        return a.get_name() < b.get_name();
    }
};

static std::map<CommandDTO, std::function<std::unique_ptr<ServiceCommand> (const CommandDTO&)>, CompareByName> creators
        {{{CommandDTO{CommandNames::UndoName}, [](const CommandDTO&){return std::make_unique<Undo>();}},
          {CommandDTO{CommandNames::RedoName}, [](const CommandDTO&){return std::make_unique<Redo>();}}}};

std::unique_ptr<ServiceCommand> ServiceCommandFactory::create(const CommandDTO &cmd) {
    return creators[cmd](cmd);
}
