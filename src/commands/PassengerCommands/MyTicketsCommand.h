#pragma once

#include <commands/CLICommand.h>
#include "core/Engine.h"
#include "users/Passenger.h"


class MyTicketsCommand final : public CLICommand {
public:
    explicit MyTicketsCommand(Engine &engine);

    [[nodiscard]] CommandRole getRequiredRole() const override;

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};
