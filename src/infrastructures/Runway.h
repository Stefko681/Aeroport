//
// Created by stefko on 5/15/26.
//

#ifndef AEROPORT_RUNWAY_H
#define AEROPORT_RUNWAY_H
#include "RunwayStatus.h"
#include "RunwayModuls.h"

class Runway {
protected:
    int runwayId;
    double length;
    RunwayStatus runwayStatus;
    RunwayModuls runwayModuls;

    bool isOccupied();

public:
    Runway(int runwayId, double length, RunwayStatus &runwayStatus, RunwayModuls &runwayModuls);
};


#endif //AEROPORT_RUNWAY_H
