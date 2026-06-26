#include "UpgradeTicketVisitor.h"

UpgradeTicketVisitor::UpgradeTicketVisitor(std::shared_ptr<Flight> f, const TicketType t)
    : flight(std::move(f)), type(t) {
}

void UpgradeTicketVisitor::visit(Passenger &passenger) {
    if (auto result = passenger.upgradeTicket(flight, type); !result)
        throw std::runtime_error(result.error());
}
