#ifndef COMMAND_FACTORY_HPP
#define COMMAND_FACTORY_HPP
#include "command_dto.hpp"
#include "command.hpp"
#include "insert.hpp"
#include "delete.hpp"
#include "copy.hpp"
#include "paste.hpp"
#include "text_processor.hpp"
#include <string>
#include <sstream>
#include <utility>
#include <map>
#include <functional>

class TextCommandFactory{
public:
    [[nodiscard]] static std::unique_ptr<Command> create(const CommandDTO& cmd);
};
#endif //COMMAND_FACTORY_HPP
