#include "UndoCommand.h"
#include "core/Engine.h"

UndoCommand::UndoCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole UndoCommand::getRequiredRole() const {
    return CommandRole::Dispatcher;
}

std::expected<void, std::string> UndoCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 1) return std::unexpected("Usage: undo");
    try {
        engine.undoLastCommand();
    } catch (const std::exception &ex) {
        return std::unexpected(ex.what());
    }
    return {};
}
