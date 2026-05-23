//
// Created by stefko on 5/14/26.
//

#ifndef AEROPORT_AIRCRAFT_H
#define AEROPORT_AIRCRAFT_H
#include <memory>
#include <string>
#include "AirplaneType.h"
#include "infrastructures/Runway.h"

class Airplane {
protected:
    std::string airplaneId;
    std::string model;
    double health;
    bool inHangar{false};

public:
    Airplane(std::string airplaneId, std::string model, double health);

    virtual ~Airplane() = default;

    [[nodiscard]] virtual AirplaneType getAirplaneType() const = 0;

    [[nodiscard]] virtual bool canLand(const Runway &runway) const = 0;

    virtual void completeFlight() = 0;

    [[nodiscard]] virtual double airportFee(double ticketRevenue) const = 0;

    [[nodiscard]] virtual int getCapacity() const = 0;

    [[nodiscard]] virtual std::unique_ptr<Airplane> clone(std::string newId) const = 0;

    [[nodiscard]] bool canFly() const;

    [[nodiscard]] const std::string &getAirplaneId() const;

    [[nodiscard]] const std::string &getModel() const;

    [[nodiscard]] double getHealth() const;

    [[nodiscard]] bool isInHangar() const;

    void restoreHealth();

    void setInHangar(bool value);
};


#endif //AEROPORT_AIRCRAFT_H
