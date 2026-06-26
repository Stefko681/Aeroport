#pragma once

#include "commands/CLICommand.h"

class SaveCommand final : public CLICommand {
public:
    explicit SaveCommand(Engine &engine);

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;

    [[nodiscard]] CommandRole getRequiredRole() const override;
};

