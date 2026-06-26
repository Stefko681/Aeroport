#include "RefundVisitor.h"
#include <print>
#include "users/Passenger.h"

RefundVisitor::RefundVisitor(std::string id) : flightId(std::move(id)) {
}

void RefundVisitor::visit(Passenger &p) {
    if (const double refunded = p.refundAllTicketsForFlight(flightId); refunded > 0.0) {
        std::println("[System] Auto-refunding {:.2f} EUR to passenger {}...", refunded, p.getName());
    }
}

void RefundVisitor::visit(TrafficControl &) {
}

void RefundVisitor::visit(AirportAuthority &) {
}
