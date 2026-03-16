//
// Created by novod on 16.03.2026.
//

#ifndef FERRY_SPEEDBOAT_H
#define FERRY_SPEEDBOAT_H
#include "Vessel.h"


class Speedboat : public Vessel {
public:
    Speedboat(int index, double m, Position pos, double sx, double sy, double dt, double drag);

};


#endif //FERRY_SPEEDBOAT_H