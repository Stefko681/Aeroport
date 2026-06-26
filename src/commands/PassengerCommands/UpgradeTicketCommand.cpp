#include "UpgradeTicketCommand.h"
#include <stdexcept>
#include "core/Engine.h"
#include "visitors/PassengerVisitors/UpgradeTicketVisitor.h"

namespace {
    TicketType stringToTicketType(const std::string &s) {
        if (s == "VIP") return TicketType::VIPTicket;
        throw std::runtime_error("You can only upgrade to VIP. Usage: upgrade-ticket [flight_id] VIP");
    }
}

UpgradeTicketCommand::UpgradeTicketCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole UpgradeTicketCommand::getRequiredRole() const {
    return CommandRole::Passenger;
}

std::expected<void, std::string> UpgradeTicketCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 3) return std::unexpected("Usage: upgrade-ticket [flight_id] [VIP]");
    const auto f = engine.findFlightGlobal(args[1]);
    if (!f) return std::unexpected("[Error] Flight '" + args[1] + "' not found.");
    TicketType type;
    try {
        type = stringToTicketType(args[2]);
    } catch (const std::exception &ex) {
        return std::unexpected(ex.what());
    }
    try {
        UpgradeTicketVisitor visitor(f, type);
        if (const auto user = engine.getCurrentUser()) user->accept(visitor);
    } catch (const std::exception &ex) {
        return std::unexpected(ex.what());
    }
    return {};
}
