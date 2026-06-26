#include "SaveUserFundsVisitor.h"

SaveUserFundsVisitor::SaveUserFundsVisitor(std::ostream &os) : out(os) {
}

void SaveUserFundsVisitor::visit(Passenger &p) {
    out << '\t' << p.getFunds();
}
