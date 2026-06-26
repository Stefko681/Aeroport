#pragma once

#include "commands/CLICommand.h"

class LoginCommand final : public CLICommand {
public:
    explicit LoginCommand(Engine &engine);

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;

    [[nodiscard]] CommandRole getRequiredRole() const override;
};


