#include "CancelTicketCommand.h"
#include "core/Engine.h"
#include "visitors/PassengerVisitors/CancelTicketVisitor.h"

CancelTicketCommand::CancelTicketCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole CancelTicketCommand::getRequiredRole() const {
    return CommandRole::Passenger;
}

std::expected<void, std::string> CancelTicketCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 2) return std::unexpected("Usage: cancel-ticket [flight_id]");
    const auto f = engine.findFlightGlobal(args[1]);
    if (!f) return std::unexpected("[Error] Flight '" + args[1] + "' not found.");
    try {
        CancelTicketVisitor visitor(f);
        if (const auto user = engine.getCurrentUser()) user->accept(visitor);
    } catch (const std::exception &ex) {
        return std::unexpected(ex.what());
    }
    return {};
}
