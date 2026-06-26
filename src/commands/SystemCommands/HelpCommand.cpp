#include "HelpCommand.h"
#include "core/Engine.h"
#include "users/User.h"
#include <print>

std::expected<void, std::string> HelpCommand::execute(const std::vector<std::string> &args) {
    const auto currentUser = engine.getCurrentUser();
    if (!currentUser) {
        std::println("");
        std::println("[System] Available commands:");
        std::println("");
        std::println("  login [username] [password]                  - Log into the system.");
        std::println("  register [username] [password] [role]        - Create new user (Passenger | Dispatcher).");
        std::println("  save                                         - Save current state to file.");
        std::println("  load                                         - Load saved state from file.");
        std::println("  help                                         - Show this help screen.");
        std::println("");
    } else {
        currentUser->help();
    }
    return {};
}

CommandRole HelpCommand::getRequiredRole() const {
    return CommandRole::Any;
}

HelpCommand::HelpCommand(Engine &engine) : CLICommand(engine) {
}
