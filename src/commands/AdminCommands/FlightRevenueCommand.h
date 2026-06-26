#pragma once

#include "commands/CLICommand.h"


class FlightRevenueCommand final : public CLICommand {
public:
    explicit FlightRevenueCommand(Engine &engine);

    [[nodiscard]] CommandRole getRequiredRole() const override;

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};


