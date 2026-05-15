//
// Created by stefko on 5/15/26.
//

#ifndef AEROPORT_HANGAR_H
#define AEROPORT_HANGAR_H
#include <string>

class Hangar {
protected:
    std::string hangarId;
    int capacity;
    double fee;

public:
    Hangar(std::string hangarId, int capacity, double fee);
};


#endif //AEROPORT_HANGAR_H
