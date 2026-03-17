//
// Created by novod on 09.03.2026.
//

#ifndef FERRY_CONTROLLER_H
#define FERRY_CONTROLLER_H
#include "Ferry.h"

class Controller {
private:
    Vessel& myVessel;
    Vector2D startPoint;
    Vector2D target;
    double Kp;
    double Ki;
    double Kd;
    double integralFwd;
    double integralLat;
    double lastErrorFwd;
    double lastErrorLat;
public:
    Controller(Vessel& f, Vector2D start, Vector2D t, double kp_value, double ki_value, double kd_value);
    void update(double dt, double waterX, double waterY);
    bool isDocked();
};


#endif //FERRY_CONTROLLER_H