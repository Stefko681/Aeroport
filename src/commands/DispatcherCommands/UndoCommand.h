#pragma once

#include "commands/CLICommand.h"
#include "commands/DispatcherCommand.h"
#include "core/Engine.h"


class UndoCommand final : public CLICommand {
public:
    explicit UndoCommand(Engine &engine);

    [[nodiscard]] CommandRole getRequiredRole() const override;

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};
