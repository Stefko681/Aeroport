#pragma once


#include "commands/CLICommand.h"


class ListFleetCommand final : public CLICommand {
public:
    explicit ListFleetCommand(Engine &engine);

    [[nodiscard]] CommandRole getRequiredRole() const override;

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};

