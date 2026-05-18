//
// Created by stefko on 5/15/26.
//

#ifndef AEROPORT_AIRLINE_H
#define AEROPORT_AIRLINE_H
#include <memory>
#include <string>
#include <vector>

class Airplane;
class Flight;

class Airline {
    std::string name;
    double balance;
    std::vector<std::unique_ptr<Airplane> > airplanes;
    std::vector<std::unique_ptr<Flight> > flights;

public:
    Airline(std::string name, double balance);

    ~Airline() = default;
};


#endif //AEROPORT_AIRLINE_H
