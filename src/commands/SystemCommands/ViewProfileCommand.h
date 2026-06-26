#pragma once


#include "commands/CLICommand.h"

class ViewProfileCommand final : public CLICommand {
public:
    explicit ViewProfileCommand(Engine &engine);

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;

    [[nodiscard]] CommandRole getRequiredRole() const override;
};

