#pragma once

#include "commands/CLICommand.h"


class CloseRunwayCommand final : public CLICommand {
public:
    explicit CloseRunwayCommand(Engine &engine);

    [[nodiscard]] CommandRole getRequiredRole() const override;

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};


