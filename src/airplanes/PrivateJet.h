//
// Created by stefko on 5/14/26.
//

#ifndef AEROPORT_PRIVITEJET_H
#define AEROPORT_PRIVITEJET_H
#include "Airplane.h"

class PrivateJet : public Airplane {
    int capacity = 12;

public:
    PrivateJet(std::string airplaneId, std::string model, double health);

    [[nodiscard]] bool canLand(const Runway &runway) const override;

    [[nodiscard]] double airportFee(double ticketRevenue) const override;

    void completeFlight() override;

    [[nodiscard]] AirplaneType getAirplaneType() const override;
};


#endif //AEROPORT_PRIVITEJET_H
