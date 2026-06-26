#pragma once

#include "commands/CLICommand.h"


class AuditAirlineCommand final : public CLICommand {
public:
    explicit AuditAirlineCommand(Engine &engine);

    [[nodiscard]] CommandRole getRequiredRole() const override;

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};


