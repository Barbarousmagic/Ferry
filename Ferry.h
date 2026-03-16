//
// Created by novod on 09.03.2026.
//

#ifndef FERRY_FERRY_H
#define FERRY_FERRY_H
#include "Vessel.h"

class Ferry : public Vessel {
private:
    Ferry* nextFerry;

public:
    Ferry(int index, double m, Position pos, double sx, double sy, double dt, double drag);
    Position calcDist(double waterX, double waterY) const;
    Ferry* getNextFerry ();
    void setNextFerry(Ferry* next);
};


#endif //FERRY_FERRY_H