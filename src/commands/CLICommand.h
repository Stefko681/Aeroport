#pragma once

#include <expected>
#include  <vector>
#include <string>

class Engine;

enum class CommandRole {
    Guest,
    Any,
    Passenger,
    Dispatcher,
    Admin
};

class CLICommand {
protected:
    Engine &engine;

public:
    explicit CLICommand(Engine &engine);

    virtual ~CLICommand() = default;

    virtual std::expected<void, std::string> execute(const std::vector<std::string> &args) = 0;

    [[nodiscard]] virtual CommandRole getRequiredRole() const = 0;

    [[nodiscard]] virtual bool isUndoable() const;

    virtual void undo();

    [[nodiscard]] virtual std::string description() const;
};


