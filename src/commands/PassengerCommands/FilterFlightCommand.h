#pragma once


#include "commands/CLICommand.h"

class FilterFlightsCommand final : public CLICommand {
public:
    explicit FilterFlightsCommand(Engine &engine);

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;

    [[nodiscard]] CommandRole getRequiredRole() const override;
};

