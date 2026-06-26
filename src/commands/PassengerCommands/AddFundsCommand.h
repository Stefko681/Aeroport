#pragma once


#include "commands/CLICommand.h"

class AddFundsCommand final : public CLICommand {
public:
    explicit AddFundsCommand(Engine &engine);

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;

    [[nodiscard]] CommandRole getRequiredRole() const override;
};

