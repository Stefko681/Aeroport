#include "AddBaggageVisitor.h"

AddBaggageVisitor::AddBaggageVisitor(std::shared_ptr<Flight> f, const double w)
    : flight(std::move(f)), weight(w) {
}

void AddBaggageVisitor::visit(Passenger &passenger) {
    if (auto result = passenger.addBaggage(flight, weight); !result)
        throw std::runtime_error(result.error());
}
