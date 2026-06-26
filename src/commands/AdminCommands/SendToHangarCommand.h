#pragma once

#include "commands/CLICommand.h"


class SendToHangarCommand final : public CLICommand {
public:
    explicit SendToHangarCommand(Engine &engine);

    [[nodiscard]] CommandRole getRequiredRole() const override;

    std::expected<void, std::string> execute(const std::vector<std::string> &args) override;
};


