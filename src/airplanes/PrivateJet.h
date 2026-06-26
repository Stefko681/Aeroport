#pragma once

#include "Airplane.h"


class PrivateJet : public Airplane {
    static constexpr size_t CAPACITY = 12;

public:
    PrivateJet(std::string model, double health);

    [[nodiscard]] AirplaneType getAirplaneType() const override;

    [[nodiscard]] bool canLand(const Runway &runway) const override;

    [[nodiscard]] double airportFee(double ticketRevenue) const override;

    [[nodiscard]] size_t getAirplaneCapacity() const override;

    void completeFlight() override;

    [[nodiscard]] std::unique_ptr<Airplane> clone() const override;

    void accept(AirplaneVisitor &visitor) override;
};


