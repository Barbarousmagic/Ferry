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
    Ferry(int index, double m, Vector2D pos, double sx, double sy, double dt, double drag);
    Vector2D calcDist(double waterX, double waterY) const;
    Ferry* getNextFerry ();
    void setNextFerry(Ferry* next);
};


#endif //FERRY_FERRY_H