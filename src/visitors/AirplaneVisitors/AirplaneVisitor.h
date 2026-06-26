#pragma once


class PrivateJet;
class CargoPlane;
class PassengerPlane;

class AirplaneVisitor {
public:
    virtual ~AirplaneVisitor() = default;

    virtual void visit(PassengerPlane &plane) = 0;

    virtual void visit(CargoPlane &plane) = 0;

    virtual void visit(PrivateJet &plane) = 0;
};

