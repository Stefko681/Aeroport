#pragma once

#include "commands/CLICommand.h"
#include "operations/Flight.h"
#include <users/Passenger.h>

class AddBaggageCommand final : public CLICommand {
public:
    explicit AddBaggageCommand(Engine &engine);

    [[nodiscard]] CommandRole getRequiredRole() const override;

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};
