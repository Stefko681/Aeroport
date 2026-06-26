#pragma once

#include "commands/CLICommand.h"
#include "core/Engine.h"

class RegisterAirlineCommand final : public CLICommand {
public:
    explicit RegisterAirlineCommand(Engine &engine);

    [[nodiscard]] CommandRole getRequiredRole() const override;

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};
