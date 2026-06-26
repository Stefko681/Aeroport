#include "RegisterCommand.h"
#include "core/Engine.h"
#include "users/Passenger.h"
#include "users/TrafficControl.h"
#include <print>

RegisterCommand::RegisterCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole RegisterCommand::getRequiredRole() const {
    return CommandRole::Guest;
}

std::expected<void, std::string> RegisterCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 4) return std::unexpected("Usage: register [username] [password] [Passenger|Dispatcher]");
    const std::string &username = args[1];
    const std::string &password = args[2];
    const std::string &roleStr = args[3];
    if (engine.findUser(username)) return std::unexpected("[Error] Username '" + username + "' already exists.");
    std::shared_ptr<User> newUser;
    if (roleStr == "Passenger") {
        newUser = std::make_shared<Passenger>(username, password);
    } else if (roleStr == "Dispatcher") {
        newUser = std::make_shared<TrafficControl>(username, password);
    } else if (roleStr == "Administrator" || roleStr == "Admin") {
        return std::unexpected("Cannot register a System Administrator. Only one admin exists.");
    } else {
        return std::unexpected("Unknown role '" + roleStr + "'. Use 'Passenger' or 'Dispatcher'.");
    }
    engine.addUser(newUser);
    std::println("[System] User '{}' registered successfully (Role: {}).", username, roleStr);
    return {};
}
