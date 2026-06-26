#pragma once


#include "commands/CLICommand.h"
#include "core/Engine.h"
#include <stdexcept>

class ListRunwaysCommand final : public CLICommand {
public:
    explicit ListRunwaysCommand(Engine &engine);

    [[nodiscard]] CommandRole getRequiredRole() const override;

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};

