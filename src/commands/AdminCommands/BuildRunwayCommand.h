#pragma once

#include "commands/CLICommand.h"

class BuildRunwayCommand final : public CLICommand {
public:
    explicit BuildRunwayCommand(Engine &engine);

    [[nodiscard]] CommandRole getRequiredRole() const override;

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};


