//
// Created by novod on 09.03.2026.
//

#ifndef FERRY_CONTROLLER_H
#define FERRY_CONTROLLER_H
#include "Ferry.h"

class Controller {
private:
    Ferry myFerry;
    Position target;
public:
    Controller(Ferry f, Position t);
    bool isDockingSuccessful(double waterX, double waterY);
};


#endif //FERRY_CONTROLLER_H