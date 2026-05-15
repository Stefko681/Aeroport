//
// Created by stefko on 5/14/26.
//

#ifndef AEROPORT_PASSENEGERPLANE_H
#define AEROPORT_PASSENEGERPLANE_H
#include "Airplane.h"

class PassengerPlane : public Airplane {
private:
    int maxPassengers;

public:
    PassengerPlane(std::string airplaneId, std::string model, int health, int maxPassengers);

    [[nodiscard]] bool canLand(const Runway &runway) const override;

    void completeFlight() override;

    [[nodiscard]] double airportFee(double ticketRevenue) const override;

    [[nodiscard]] AirplaneType getAirplaneType() const override;
};


#endif //AEROPORT_PASSENEGERPLANE_H
