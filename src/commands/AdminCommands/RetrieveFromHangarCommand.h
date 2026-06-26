#pragma once

#include "commands/CLICommand.h"


class RetrieveFromHangarCommand final : public CLICommand {
public:
    explicit RetrieveFromHangarCommand(Engine &engine);

    [[nodiscard]] CommandRole getRequiredRole() const override;

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};


