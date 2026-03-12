//
// Created by novod on 09.03.2026.
//

#ifndef FERRY_CONTROLLER_H
#define FERRY_CONTROLLER_H
#include "Ferry.h"

class Controller {
private:
    Ferry& myFerry;
    Position target;
    double Kp;
    double Ki;
    double Kd;
    double integralX;
    double integralY;
    double lastErrorX;
    double lastErrorY;
public:
    Controller(Ferry& f, Position t, double kp_value, double ki_value, double kd_value);
    void update(double dt);
    bool isDocked();
};


#endif //FERRY_CONTROLLER_H