#include "RegisterAirlineCommand.h"
#include <print>
#include <memory>
#include "core/Engine.h"

RegisterAirlineCommand::RegisterAirlineCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole RegisterAirlineCommand::getRequiredRole() const {
    return CommandRole::Admin;
}

std::expected<void, std::string> RegisterAirlineCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 3) return std::unexpected("Usage: register-airline [name] [initial_capital]");
    double initialCapital;
    try {
        initialCapital = std::stod(args[2]);
    }
    catch (...) {
        return std::unexpected("[Error] Invalid initial capital provided.");
    }
    try {
        engine.addAirline(std::make_shared<Airline>(args[1], initialCapital));
    } catch (const std::exception &ex) {
        return std::unexpected(ex.what());
    }
    std::println("[Admin] Airline '{}' registered. Corporate Balance: {:.2f} EUR.", args[1], initialCapital);
    return {};
}
