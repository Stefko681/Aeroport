#include "AddFundsVisitor.h"

AddFundsVisitor::AddFundsVisitor(const double amt) : amount(amt) {
}

void AddFundsVisitor::visit(Passenger &passenger) {
    passenger.addFunds(amount);
}
