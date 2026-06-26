#include "AirportReportCommand.h"
#include <print>
#include "operations/Flight.h"
#include "../../visitors/UserVisitors/AirportReportVisitor.h"
#include "core/Engine.h"

AirportReportCommand::AirportReportCommand(Engine &engine) : CLICommand(engine) {
}

CommandRole AirportReportCommand::getRequiredRole() const {
    return CommandRole::Admin;
}

std::expected<void, std::string> AirportReportCommand::execute(const std::vector<std::string> &args) {
    if (args.size() > 1) return std::unexpected("Usage: airport-report (no arguments required)");
    AirportReportVisitor visitor;
    for (const auto &airline: engine.getAirlines()) {
        for (const auto &flight: airline->getAllFlights()) {
            if (flight->getFlightStatus() == FlightStatus::Departed) {
                visitor.process(*flight);
            }
        }
    }
    std::println("=== Global Airport Financial Report ===\n"
                 "Taxes from Passenger Flights: {:.2f} EUR\n"
                 "Taxes from Cargo Flights: {:.2f} EUR\n"
                 "Taxes from Private Flights: {:.2f} EUR\n"
                 "---------------------------------------\n"
                 "Total Airport Revenue Generated: {:.2f} EUR",
                 visitor.getPassengerTax(),
                 visitor.getCargoTax(),
                 visitor.getPrivateTax(),
                 visitor.getTotal());
    return {};
}
