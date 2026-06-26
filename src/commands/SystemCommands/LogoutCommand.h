#pragma once

#include "commands/CLICommand.h"

class LogoutCommand final : public CLICommand {
public:
    explicit LogoutCommand(Engine &engine);

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;

    [[nodiscard]] CommandRole getRequiredRole() const override;
};

