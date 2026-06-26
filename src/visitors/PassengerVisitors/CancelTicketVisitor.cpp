#include "CancelTicketVisitor.h"

CancelTicketVisitor::CancelTicketVisitor(std::shared_ptr<Flight> f)
    : flight(std::move(f)) {
}

void CancelTicketVisitor::visit(Passenger &passenger) {
    if (auto result = passenger.cancelTicket(flight); !result)
        throw std::runtime_error(result.error());
}