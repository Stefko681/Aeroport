#pragma once

#include "../AirplaneVisitors/AirplaneVisitor.h"


class Flight;

class AirportReportVisitor final : public AirplaneVisitor {
    double passengerTax{0.0};
    double cargoTax{0.0};
    double privateTax{0.0};
    double currentTax{0.0};

public:
    [[nodiscard]] double getPassengerTax() const;

    [[nodiscard]] double getCargoTax() const;

    [[nodiscard]] double getPrivateTax() const;

    [[nodiscard]] double getTotal() const;

    void process(const Flight &flight);

    void visit(PassengerPlane &plane) override;

    void visit(CargoPlane &plane) override;

    void visit(PrivateJet &plane) override;
};


