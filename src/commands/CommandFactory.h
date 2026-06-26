#pragma once


#include <memory>
#include <string>

class CLICommand;
class Engine;

class CommandFactory {
public:
    static std::shared_ptr<CLICommand> create(const std::string &commandName, Engine &engine);
};

