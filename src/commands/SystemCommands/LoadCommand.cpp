#include "LoadCommand.h"
#include "core/Engine.h"
#include "../../core/SaveManager.h"
#include <print>

LoadCommand::LoadCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole LoadCommand::getRequiredRole() const {
    return CommandRole::Any;
}

std::expected<void, std::string> LoadCommand::execute(const std::vector<std::string> &args) {
    try {
        if (SaveManager::load(engine)) {
            std::println("[System] State loaded successfully from '{}'.", SaveManager::DEFAULT_FILE);
        } else {
            std::println("[System] No save file found. Starting a fresh instance of AeroPort System.");
        }
        return {};
    } catch (const std::exception &ex) {
        return std::unexpected(std::string("[Error] Failed to load save file: ") + ex.what());
    }
}
