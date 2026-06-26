#include "LoadTicketVisitor.h"
#include "users/Passenger.h"

LoadTicketVisitor::LoadTicketVisitor(const TicketType t, std::shared_ptr<Flight> f, const double p,
                                     const double b) : type(t), flight(std::move(f)), paid(p), baggage(b) {
}

void LoadTicketVisitor::visit(Passenger &p) {
    p.loadTicket(type, flight, paid, baggage);
}
