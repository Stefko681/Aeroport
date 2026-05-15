//
// Created by stefko on 5/14/26.
//

#ifndef AEROPORT_CARGOPLANE_H
#define AEROPORT_CARGOPLANE_H
#include "Airplane.h"

class CargoPlane : public Airplane {
    double maxWeigh;

public:
    CargoPlane(std::string airplaneId, std::string model, double health, double maxWeigh);

    [[nodiscard]] AirplaneType getAirplaneType() const override;

    [[nodiscard]] bool canLand(double length, bool hasVIPTerminal) const override;

    void completeFlight() override;

    [[nodiscard]] double airportFee(double ticketRevenue) const override;
};


#endif //AEROPORT_CARGOPLANE_H
