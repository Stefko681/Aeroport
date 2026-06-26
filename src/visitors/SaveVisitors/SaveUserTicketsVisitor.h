#pragma once
#include "../../users/Passenger.h"
#include <iosfwd>
#include <string>
#include "../UserVisitors/UserVisitor.h"

enum class TicketType;

class SaveUserTicketsVisitor : public UserVisitor {
    std::ostream &out;
    std::string name;

    static std::string sanitize(std::string s);

    static const char *ticketTypeStr(TicketType t);

public:
    SaveUserTicketsVisitor(std::ostream &os, std::string n);

    void visit(Passenger &p) override;
};

