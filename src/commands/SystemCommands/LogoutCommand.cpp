#include "LogoutCommand.h"
#include "core/Engine.h"
#include <print>

LogoutCommand::LogoutCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole LogoutCommand::getRequiredRole() const {
    return CommandRole::Any;
}

std::expected<void, std::string> LogoutCommand::execute(const std::vector<std::string> &args) {
    if (!engine.getCurrentUser()) return std::unexpected("[Error] No user is currently logged in.");
    engine.setCurrentUser(nullptr);
    std::println("[System] Logged out successfully.");
    return {};
}
