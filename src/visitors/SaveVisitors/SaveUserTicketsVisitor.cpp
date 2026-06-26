#include "SaveUserTicketsVisitor.h"
#include <string>
#include <iostream>
#include "../../tickets/Ticket.h"

class Passenger;

std::string SaveUserTicketsVisitor::sanitize(std::string s) {
    for (char &c: s)
        if (c == '\t' || c == '\n' || c == '\r') c = ' ';
    return s;
}

const char *SaveUserTicketsVisitor::ticketTypeStr(TicketType t) {
    switch (t) {
        case TicketType::StandardTicket: return "Standard";
        case TicketType::LastMinuteTicket: return "LastMinute";
        case TicketType::VIPTicket: return "VIP";
    }
    return "Unknown";
}

SaveUserTicketsVisitor::SaveUserTicketsVisitor(std::ostream &os, std::string n)
    : out(os), name(std::move(n)) {
}

void SaveUserTicketsVisitor::visit(Passenger &p) {
    for (const auto &[flightId, type, paid, baggage]: p.getTicketSnapshot()) {
        out << sanitize(name) << '\t' << sanitize(flightId) << '\t' << ticketTypeStr(type) << '\t' << paid << '\t' <<
                baggage << '\n';
    }
}
