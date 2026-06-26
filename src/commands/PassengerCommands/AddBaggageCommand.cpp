#include "AddBaggageCommand.h"
#include "core/Engine.h"
#include "visitors/PassengerVisitors/AddBaggageVisitor.h"

AddBaggageCommand::AddBaggageCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole AddBaggageCommand::getRequiredRole() const {
    return CommandRole::Passenger;
}

std::expected<void, std::string> AddBaggageCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 3) return std::unexpected("Usage: add-baggage [flight_id] [weight]");
    const auto f = engine.findFlightGlobal(args[1]);
    if (!f) return std::unexpected("[Error] Flight '" + args[1] + "' not found.");
    try {
        const double w = std::stod(args[2]);
        AddBaggageVisitor visitor(f, w);
        if (const auto user = engine.getCurrentUser()) user->accept(visitor);
    } catch (const std::exception &ex) {
        return std::unexpected(ex.what());
    }
    return {};
}
