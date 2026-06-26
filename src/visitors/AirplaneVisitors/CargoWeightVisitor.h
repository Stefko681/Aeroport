#pragma once

#include <iostream>

#include "AirplaneVisitor.h"

class CargoWeightVisitor final : public AirplaneVisitor {
    size_t weight{0};

public:
    void visit(CargoPlane &plane) override;

    void visit(PassengerPlane &plane) override;

    void visit(PrivateJet &plane) override;

    [[nodiscard]] size_t getWeight() const;
};

