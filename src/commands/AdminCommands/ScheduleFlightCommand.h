#pragma once

#include "commands/CLICommand.h"


class ScheduleFlightCommand final : public CLICommand {
public:
    explicit ScheduleFlightCommand(Engine &engine);

    [[nodiscard]] CommandRole getRequiredRole() const override;

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};


