#pragma once

#include "commands/CLICommand.h"


class CloneAircraftCommand final : public CLICommand {
public:
    explicit CloneAircraftCommand(Engine &engine);

    [[nodiscard]] CommandRole getRequiredRole() const override;

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};


