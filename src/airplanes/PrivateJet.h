//
// Created by stefko on 5/14/26.
//

#ifndef AEROPORT_PRIVITEJET_H
#define AEROPORT_PRIVITEJET_H
#include "Airplane.h"


class PrivateJet : public Airplane {
    static constexpr int CAPACITY = 12;

public:
    PrivateJet(std::string airplaneId, std::string model, double health);

    [[nodiscard]] AirplaneType getAirplaneType() const override;

    [[nodiscard]] bool canLand(const Runway &runway) const override;

    [[nodiscard]] double airportFee(double ticketRevenue) const override;

    [[nodiscard]] int getCapacity() const override;

    std::unique_ptr<Airplane> clone(std::string newId) const override;

    void completeFlight() override;
};


#endif //AEROPORT_PRIVITEJET_H
