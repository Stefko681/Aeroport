#include "BookTicketCommand.h"
#include <stdexcept>
#include "core/Engine.h"
#include "tickets/Ticket.h"
#include "visitors/PassengerVisitors/BookTicketVisitor.h"

class Flight;

BookTicketCommand::BookTicketCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole BookTicketCommand::getRequiredRole() const {
    return CommandRole::Passenger;
}

std::expected<void, std::string> BookTicketCommand::execute(const std::vector<std::string> &args) {
    if (args.size() < 3) return std::unexpected("Usage: book-ticket [flight_id] [Standard|Last Minute|VIP]");
    const auto f = engine.findFlightGlobal(args[1]);
    if (!f) return std::unexpected("[Error] Flight '" + args[1] + "' not found.");
    std::string typeStr = args[2];
    for (size_t i = 3; i < args.size(); ++i) {
        typeStr += " " + args[i];
    }
    TicketType type;
    try {
        type = stringToTicketType(typeStr);
    } catch (const std::exception &ex) {
        return std::unexpected(ex.what());
    }
    try {
        BookTicketVisitor visitor(f, type);
        engine.getCurrentUser()->accept(visitor);
    } catch (const std::exception &ex) {
        return std::unexpected(ex.what());
    }
    return {};
}
