//
// Created by stefko on 5/14/26.
//

#ifndef AEROPORT_AIRCRAFT_H
#define AEROPORT_AIRCRAFT_H
#include <string>
#include "AirplaneType.h"

class Airplane {
protected:
    std::string airplaneId;
    std::string model;
    int health;
    AirplaneType airplaneType;

public:
    Airplane(std::string &airplaneId, std::string &model, int health, AirplaneType &airplaneType);
};


#endif //AEROPORT_AIRCRAFT_H
