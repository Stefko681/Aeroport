#pragma once


#include "commands/CLICommand.h"

class BookTicketCommand final : public CLICommand {
public:
    explicit BookTicketCommand(Engine &engine);

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;

    [[nodiscard]] CommandRole getRequiredRole() const override;
};

