#pragma once

#include "commands/CLICommand.h"
#include "core/Engine.h"


class BuyAircraftCommand final : public CLICommand {
public:
    explicit BuyAircraftCommand(Engine &engine);

    [[nodiscard]] CommandRole getRequiredRole() const override;

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};
