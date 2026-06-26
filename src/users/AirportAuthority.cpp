#include "AirportAuthority.h"
#include <print>

AirportAuthority::AirportAuthority(std::string name, std::string password) : User(
    std::move(name), std::move(password)) {
}

UserRole AirportAuthority::getUserRole() const {
    return UserRole::AirportAuthority;
}

void AirportAuthority::viewProfile() const {
    std::println("[Profile] User: {} | Role: System Administrator | Privilege: ALL_ACCESS", name);
}


void AirportAuthority::help() const {
    std::println("[System] Available commands for Administrator:");
    std::println(
        "  register-airline [name] [initial_capital]                                - Register a new airline in the system with the given starting balance.");
    std::println(
        "  buy-aircraft     [airline_name] [type] [model] [capacity/tonnage]        - Purchase an aircraft for a fleet (10 000 EUR, Health = 100 %).");
    std::println(
        "  clone-aircraft   [id] [count]                                            - Create exact copies of an existing aircraft.");
    std::println(
        "  send-to-hangar   [aircraft_id] [hangar_id]                               - Send aircraft to hangar for repair (fee deducted from balance).");
    std::println(
        "  schedule-flight  [flight_id] [aircraft_id] [destination] [base_price]    - Create a Scheduled flight (requires aircraft Health >= 20 %).");
    std::println(
        "  retrieve-from-hangar [aircraft_id]                                       - Retrieve aircraft from hangar; Health restored to 100 %.");
    std::println(
        "  cancel-flight    [flight_id]                                             - Cancel a flight and automatically refund all passengers.");
    std::println(
        "  flight-revenue   [flight_id]                                             - Show ticket-revenue report for a specific flight.");
    std::println(
        "  list-fleet       [airline_name]                                          - List every aircraft of an airline with model and current Health %.");
    std::println(
        "  airport-report                                                           - Breakdown of airport fees by aircraft category across all Departed flights.");
    std::println(
        "  audit-airline    [airline_name]                                          - Full airline report: aircraft count, completed flights, current balance.");
    std::println("  view-profile                                                             - Show your profile.");
    std::println("  logout                                                                   - Log out.");
    std::println(
        "  save                                                                     - Persist current application state to file.");
    std::println(
        "  load                                                                     - Restore previously saved state from file.");
}

void AirportAuthority::accept(UserVisitor &visitor) {
    visitor.visit(*this);
}
