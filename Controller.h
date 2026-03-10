//
// Created by novod on 09.03.2026.
//

#ifndef FERRY_CONTROLLER_H
#define FERRY_CONTROLLER_H
#include "Ferry.h"

class Controller {
private:
    Ferry myFerry;
    double targetX;
    double targetY;
public:
    Controller(Ferry f, double tX, double tY);
    bool checkCollision(double waterX, double waterY);
};


#endif //FERRY_CONTROLLER_H