//
// Created by stefko on 5/14/26.
//

#ifndef AEROPORT_PASSENEGERPLANE_H
#define AEROPORT_PASSENEGERPLANE_H
#include "Airplane.h"

class PassengerPlane : public Airplane {
    int maxPassengers;

public:
    PassengerPlane(std::string airplaneId, std::string model, double health, int maxPassengers);

    [[nodiscard]] AirplaneType getAirplaneType() const override;

    [[nodiscard]] bool canLand(const Runway &runway) const override;

    [[nodiscard]] double airportFee(double ticketRevenue) const override;

    [[nodiscard]] int getCapacity() const override;

    [[nodiscard]] std::unique_ptr<Airplane> clone(std::string newId) const override;

    void completeFlight() override;
};

#endif //AEROPORT_PASSENEGERPLANE_H
