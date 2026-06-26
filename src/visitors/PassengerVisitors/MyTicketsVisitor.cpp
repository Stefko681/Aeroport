#include "MyTicketsVisitor.h"

void MyTicketsVisitor::visit(Passenger &passenger) {
    passenger.printMyTickets();
}
