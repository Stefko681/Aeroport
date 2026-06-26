#include "UserVisitor.h"

UserVisitor::~UserVisitor() = default;

void UserVisitor::visit(Passenger &) {
}

void UserVisitor::visit(TrafficControl &) {
}

void UserVisitor::visit(AirportAuthority &) {
}
