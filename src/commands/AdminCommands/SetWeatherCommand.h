#pragma once


#include <print>
#include "commands/CLICommand.h"

class Engine;

class SetWeatherCommand final : public CLICommand {
public:
    explicit SetWeatherCommand(Engine &engine);
    [[nodiscard]] CommandRole getRequiredRole() const override;
    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};
