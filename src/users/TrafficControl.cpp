#include "TrafficControl.h"
#include <print>

UserRole TrafficControl::getUserRole() const {
    return UserRole::TrafficControl;
}

TrafficControl::TrafficControl(std::string name, std::string password) : User(std::move(name), std::move(password)) {
}

void TrafficControl::viewProfile() const {
    std::println("[Profile] User: {} | Role: Dispatcher", name);
}

void TrafficControl::help() const {
    std::println("[System] Available commands for Dispatcher:");
    std::println("  list-airspace                       - Show flights waiting for runway assignment.");
    std::println("  list-runways                        - Show all runways with their status.");
    std::println("  assign-runway [flight_id] [runway]  - Assign a runway to a flight.");
    std::println("  delay-flight  [flight_id] [reason]  - Mark a flight as delayed.");
    std::println("  free-runway   [runway_id]           - Free a runway; flight becomes Departed.");
    std::println("  undo                                - Revert the last dispatcher command.");
    std::println("  view-profile                        - Show your profile.");
    std::println("  logout                              - Log out.");
}

void TrafficControl::accept(UserVisitor &visitor) {
    visitor.visit(*this);
}