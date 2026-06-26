#pragma once


#include "CLICommand.h"
#include <string>

class DispatcherCommand : public CLICommand {
public:
    explicit DispatcherCommand(Engine &engine);

    [[nodiscard]] bool isUndoable() const override { return true; }

    void undo() override = 0;

    [[nodiscard]] std::string description() const override = 0;

    [[nodiscard]] CommandRole getRequiredRole() const override;
};

