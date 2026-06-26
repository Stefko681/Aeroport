#pragma once

#include "commands/CLICommand.h"
#include "core/Engine.h"
#include <print>

class ListAirspaceCommand final : public CLICommand {
public:
    explicit ListAirspaceCommand(Engine &engine);

    [[nodiscard]] CommandRole getRequiredRole() const override;

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};
