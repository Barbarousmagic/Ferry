//
// Created by novod on 09.03.2026.
//

#include "Controller.h"
#include <cmath>
Controller::Controller(Ferry& f, Position t, double kp_value, double ki_value, double kd_value)
    : myFerry(f), target(t), Kp(kp_value), Ki(ki_value), Kd(kd_value),
        integralX(0.0), integralY(0.0), lastErrorX(0.0), lastErrorY(0.0) {}

void Controller::update(double dt) {
    Position currentPos = myFerry.getPos();

    double errorX = target.x - currentPos.x;
    double errorY = target.y - currentPos.y;

    integralX += errorX * dt;
    integralY += errorY * dt;

    double maxIntegral = 75000.0;
    if (integralX > maxIntegral) integralX = maxIntegral;
    if (integralX < -maxIntegral) integralX = -maxIntegral;
    if (integralY > maxIntegral) integralY = maxIntegral;
    if (integralY < -maxIntegral) integralY = -maxIntegral;

    double derivativeX = (errorX - lastErrorX) / dt;
    double derivativeY = (errorX - lastErrorY) / dt;

    double thrustX = Kp * errorX + Ki * integralX + Kd * derivativeX;
    double thrustY = Kp * errorY + Ki * integralY + Kd * derivativeY;
    myFerry.setThrust(thrustX, thrustY);
    lastErrorX = errorX;
    lastErrorY = errorY;
}

bool Controller::isDocked() {
    Position currentPos = myFerry.getPos();
    double errorX = target.x - currentPos.x;
    double errorY = target.y - currentPos.y;
    double distance = std::sqrt(errorX * errorX + errorY * errorY);

    return distance < 10.0;
}
