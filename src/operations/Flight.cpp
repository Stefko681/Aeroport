//
// Created by stefko on 5/15/26.
//

#include "Flight.h"

void Flight::replaceSoldTicket(const Ticket *oldTicket, Ticket *newTicket) {
    for (auto &ticket: soldTickets) {
        if (ticket == oldTicket) {
            ticket = newTicket;
        }
    }
}

void Flight::unregisterSoldTicket(Ticket *ticketToRemove) {
    const auto it = std::ranges::find(soldTickets, ticketToRemove);
    if (it == soldTickets.end()) throw std::runtime_error("Ticket is not existing");
    soldTickets.erase(it);
}
