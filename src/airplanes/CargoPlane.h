//
// Created by stefko on 5/14/26.
//

#ifndef AEROPORT_CARGOPLANE_H
#define AEROPORT_CARGOPLANE_H
#include "Airplane.h"

class CargoPlane : public Airplane {
    double maxWeight;

public:
    CargoPlane(std::string airplaneId, std::string model, double health, double maxWeight);

    [[nodiscard]] AirplaneType getAirplaneType() const override;

    [[nodiscard]] bool canLand(const Runway &runway) const override;

    void completeFlight() override;

    [[nodiscard]] double airportFee(double ticketRevenue) const override;
};


#endif //AEROPORT_CARGOPLANE_H
