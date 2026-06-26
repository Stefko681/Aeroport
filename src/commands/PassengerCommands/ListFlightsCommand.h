#pragma once


#include "commands/CLICommand.h"

class ListFlightsCommand final : public CLICommand {
public:
    explicit ListFlightsCommand(Engine &engine);

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;

    [[nodiscard]] CommandRole getRequiredRole() const override;
};

