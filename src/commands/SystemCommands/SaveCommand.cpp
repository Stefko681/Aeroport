#include "SaveCommand.h"
#include "core/Engine.h"
#include "core/SaveManager.h"
#include <print>

SaveCommand::SaveCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole SaveCommand::getRequiredRole() const {
    return CommandRole::Any;
}

std::expected<void, std::string> SaveCommand::execute(const std::vector<std::string> &args) {
    if (SaveManager::save(engine)) {
        std::println("[System] AeroPort application state successfully serialized and saved to '{}'.",
                     SaveManager::DEFAULT_FILE);
        return {};
    }
    return std::unexpected(std::format("[Error] Failed to write save file '{}'.", SaveManager::DEFAULT_FILE));
}
