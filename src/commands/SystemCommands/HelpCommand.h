#pragma once


#include "commands/CLICommand.h"


class HelpCommand final : public CLICommand {
public:
    explicit HelpCommand(Engine &engine);

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;

    [[nodiscard]] CommandRole getRequiredRole() const override;
};


