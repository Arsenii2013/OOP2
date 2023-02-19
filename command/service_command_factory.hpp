//
// Created by sescer on 07.12.22.
//

#ifndef COMMAND_SERVICE_COMMAND_FACTORY_HPP
#define COMMAND_SERVICE_COMMAND_FACTORY_HPP
#include <map>
#include <functional>

#include "command.hpp"
#include "service_command.hpp"
#include "command_names.hpp"

class ServiceCommandFactory{
public:
    [[nodiscard]] static std::unique_ptr<ServiceCommand> create(const CommandDTO& cmd);
};
#endif //COMMAND_SERVICE_COMMAND_FACTORY_HPP
