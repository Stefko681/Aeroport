#include "AuditAirlineCommand.h"
#include "core/Engine.h"
#include "operations/Airline.h"

AuditAirlineCommand::AuditAirlineCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole AuditAirlineCommand::getRequiredRole() const {
    return CommandRole::Admin;
}

std::expected<void, std::string> AuditAirlineCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 2) return std::unexpected("Usage: audit-airline [airline]");
    const auto airline = engine.findAirline(args[1]);
    if (!airline) return std::unexpected("Airline not found.");
    airline->printAuditReport();
    return {};
}
