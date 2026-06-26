#include "BookTicketVisitor.h"

BookTicketVisitor::BookTicketVisitor(std::shared_ptr<Flight> f, const TicketType t)
    : flight(std::move(f)), type(t) {
}

void BookTicketVisitor::visit(Passenger &passenger) {
    if (auto result = passenger.bookTicket(flight, type); !result)
        throw std::runtime_error(result.error());
}
