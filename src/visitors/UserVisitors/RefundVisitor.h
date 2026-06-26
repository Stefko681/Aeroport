#pragma once


#include "core/Engine.h"


class RefundVisitor : public UserVisitor {
    std::string flightId;

public:
    explicit RefundVisitor(std::string id);

    void visit(Passenger &p) override;

    void visit(TrafficControl &) override;

    void visit(AirportAuthority &) override;
};


