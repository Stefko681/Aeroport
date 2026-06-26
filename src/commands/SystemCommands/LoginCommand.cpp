#include "LoginCommand.h"
#include "core/Engine.h"
#include "users/User.h"
#include <print>

LoginCommand::LoginCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole LoginCommand::getRequiredRole() const {
    return CommandRole::Guest;
}

std::expected<void, std::string> LoginCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 3) return std::unexpected("Usage: login [username] [password]");
    const auto user = engine.findUser(args[1]);
    if (!user || !user->checkPassword(args[2])) return std::unexpected("Invalid credentials. Please try again.");
    engine.setCurrentUser(user);
    std::string roleStr;
    switch (user->getUserRole()) {
        case UserRole::Passenger: roleStr = "Passenger";
            break;
        case UserRole::TrafficControl: roleStr = "Dispatcher";
            break;
        case UserRole::AirportAuthority: roleStr = "System Administrator";
            break;
    }
    std::println("[System] Successfully logged in. Role: {}.", roleStr);
    return {};
}
