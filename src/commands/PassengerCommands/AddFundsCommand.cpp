#include "AddFundsCommand.h"
#include <string>
#include "commands/CLICommand.h"
#include "core/Engine.h"
#include "visitors/PassengerVisitors/AddFundsVisitor.h"

AddFundsCommand::AddFundsCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole AddFundsCommand::getRequiredRole() const {
    return CommandRole::Passenger;
}

std::expected<void, std::string> AddFundsCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 2) return std::unexpected("Usage: add-funds [amount]");
    double amount;
    try {
        amount = std::stod(args[1]);
    } catch (...) {
        return std::unexpected("[Error] Invalid amount value.");
    }
    try {
        AddFundsVisitor visitor(amount);
        engine.getCurrentUser()->accept(visitor);
    } catch (const std::exception &ex) {
        return std::unexpected(ex.what());
    }
    return {};
}
