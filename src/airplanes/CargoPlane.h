#pragma once

#include "Airplane.h"

class CargoPlane final : public Airplane {
    size_t maxWeight{0};

public:
    CargoPlane(std::string model, double health, size_t maxWeight);

    [[nodiscard]] AirplaneType getAirplaneType() const override;

    [[nodiscard]] size_t getAirplaneCapacity() const override;

    [[nodiscard]] bool canLand(const Runway &runway) const override;

    [[nodiscard]] double airportFee(double ticketRevenue) const override;

    void completeFlight() override;

    [[nodiscard]] std::unique_ptr<Airplane> clone() const override;

    void accept(AirplaneVisitor &visitor) override;
};

