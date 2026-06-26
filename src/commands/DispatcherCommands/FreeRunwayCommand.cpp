#include "FreeRunwayCommand.h"
#include "core/Engine.h"
#include "airplanes/Airplane.h"
#include "tickets/Ticket.h"
#include <print>
#include <format>
#include <ranges>
#include "../../visitors/AirplaneVisitors/CargoWeightVisitor.h"

FreeRunwayCommand::FreeRunwayCommand(Engine &engine) : DispatcherCommand(engine) {
}

std::expected<void, std::string> FreeRunwayCommand::execute(const std::vector<std::string> &args) {
    if (args.size() != 2) return std::unexpected("Usage: free-runway [runway_id]");
    runway = engine.findRunway(args[1]);
    if (!runway) return std::unexpected("[Error] Runway '" + args[1] + "' not found.");
    if (runway->getRunwayStatus() != RunwayStatus::Occupied)
        return std::unexpected("[Error] Runway " + runway->getRunwayId() + " is not Occupied.");
    auto plane = runway->getAssignedAirplane();
    if (!plane) return std::unexpected("[Error] No airplane attached to runway.");
    airline = engine.findAirlineOfAircraft(plane);
    if (!airline) return std::unexpected("[Error] Could not resolve airline for aircraft.");
    flight = nullptr;
    for (const auto &f: airline->getAllFlights()) {
        if (f->getAirplane() == plane && f->getFlightStatus() == FlightStatus::Boarding) {
            flight = f;
            break;
        }
    }
    if (!flight) return std::unexpected("[Error] No boarding flight found for this aircraft.");
    prevHealth = plane->getAirplaneHealth();
    const double rev = flight->getTotalTicketRevenue();
    const double tax = flight->getAirportTax();
    netProfitTransferred = rev - tax;
    if (auto freeRes = runway->free(); !freeRes) return std::unexpected(freeRes.error());
    flight->setFlightStatus(FlightStatus::Departed);
    plane->completeFlight();
    airline->applyFlightProfitDelta(netProfitTransferred);
    std::println("[System] Runway {} freed. Flight {} status -> Departed.", runway->getRunwayId(),
                 flight->getFlightId());
    if (plane->getAirplaneType() == AirplaneType::CargoPlane) {
        CargoWeightVisitor visitor;
        plane->accept(visitor);
        std::println(
            "[Finance] Ticket Sales: {:.2f} EUR. Cargo Tax Deducted ({:.0f}t * 15 EUR): {:.2f} EUR. Profit for {}: {:.2f} EUR.",
            rev, static_cast<double>(visitor.getWeight()), tax, airline->getName(), netProfitTransferred);
    } else {
        std::string ticketTypeStr = "Standard";
        for (const auto &weakTicket: flight->getSoldTickets() | std::views::reverse) {
            if (auto ticket = weakTicket.lock()) {
                switch (ticket->getTicketType()) {
                    case TicketType::StandardTicket: ticketTypeStr = "Standard";
                        break;
                    case TicketType::LastMinuteTicket: ticketTypeStr = "LastMinute";
                        break;
                    case TicketType::VIPTicket: ticketTypeStr = "VIP";
                        break;
                }
                break;
            }
        }
        std::println(
            "[Finance] Ticket Sales: {:.2f} EUR ({}). Airport Tax Deducted (10%): {:.2f} EUR. Profit for {}: {:.2f} EUR.",
            rev, ticketTypeStr, tax, airline->getName(), netProfitTransferred);
    }
    const double dropped = prevHealth - plane->getAirplaneHealth();
    std::println("[Health] Aircraft ID: {} health decreased by {:.0f}%. Current Health: {:.0f}%.",
                 plane->getAirplaneId(), dropped, plane->getAirplaneHealth());
    return {};
}

void FreeRunwayCommand::undo() {
    if (!flight || !airline || !runway) return;
    auto plane = flight->getAirplane();
    if (plane) plane->setHealth(prevHealth);
    airline->applyFlightProfitDelta(-netProfitTransferred);
    flight->setFlightStatus(FlightStatus::Boarding);
    if (plane) auto assignRes = runway->assign(plane);
    std::println(
        "[System] Flight {} status reverted to Boarding. Runway {} reverted to Occupied. "
        "Finances and Health states restored!", flight->getFlightId(), runway->getRunwayId());
}

std::string FreeRunwayCommand::description() const {
    if (!runway) return "free-runway (failed)";
    return "free-runway " + runway->getRunwayId();
}
