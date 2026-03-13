//
// Created by novod on 09.03.2026.
//

#ifndef FERRY_CONTROLLER_H
#define FERRY_CONTROLLER_H
#include "Ferry.h"

class Controller {
private:
    Ferry& myFerry;
    Position startPoint;
    Position target;
    double Kp;
    double Ki;
    double Kd;
    double integralFwd;
    double integralLat;
    double lastErrorFwd;
    double lastErrorLat;
public:
    Controller(Ferry& f, Position start, Position t, double kp_value, double ki_value, double kd_value);
    void update(double dt);
    bool isDocked();
};


#endif //FERRY_CONTROLLER_H