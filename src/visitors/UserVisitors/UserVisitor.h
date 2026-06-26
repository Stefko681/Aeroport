#pragma once


class Passenger;
class TrafficControl;
class AirportAuthority;

class UserVisitor {
public:
    virtual ~UserVisitor();

    virtual void visit(Passenger &passenger);

    virtual void visit(TrafficControl &dispatcher);

    virtual void visit(AirportAuthority &admin);
};

