//
// Created by novod on 09.03.2026.
//

#include "Controller.h"
#include <cmath>
Controller::Controller(Ferry& f, Position start, Position t, double kp_value, double ki_value, double kd_value)
    : myFerry(f), startPoint(start), target(t), Kp(kp_value), Ki(ki_value), Kd(kd_value),
        integralFwd(0.0), integralLat(0.0), lastErrorFwd(0.0), lastErrorLat(0.0) {}

void Controller::update(double dt, double waterX, double waterY) {
    Position currentPos = myFerry.getPos();
    double AB_x = target.x - startPoint.x;
    double AB_y = target.y - startPoint.y;

    double AP_x = currentPos.x - startPoint.x;
    double AP_y = currentPos.y - startPoint.y;

    double path_length = std::sqrt(AB_x * AB_x + AB_y * AB_y);

    double dirX = AB_x / path_length;
    double dirY = AB_y / path_length;
    double perpX = -dirY;
    double perpY = dirX;

    double errorFwd = (target.x - currentPos.x) * dirX + (target.y - currentPos.y) * dirY;
    double signedCrossProduct = AB_x * AP_y - AB_y * AP_x;
    double errorLat = signedCrossProduct / path_length; // XTE

    integralFwd += errorFwd * dt;
    integralLat += errorLat * dt;
    // Anti-Windup
    double maxIntegral = 50000.0;
    if (integralFwd > maxIntegral) integralFwd = maxIntegral;
    if (integralFwd < -maxIntegral) integralFwd = -maxIntegral;
    if (integralLat > maxIntegral) integralLat = maxIntegral;
    if (integralLat < -maxIntegral) integralLat = -maxIntegral;
    if (lastErrorFwd == 0.0 && lastErrorLat == 0.0) {
        lastErrorFwd = errorFwd;
        lastErrorLat = errorLat;
    }

    double derivFwd = (errorFwd - lastErrorFwd) / dt;
    double derivLat = (errorLat - lastErrorLat) / dt;
    double forwardThrust = Kp * errorFwd + Ki * integralFwd + Kd * derivFwd;
    double lateralThrust = 15 * Kp * (-errorLat) + Ki * (-integralLat) + 15 * Kd * (-derivLat);


    double thrustX = (forwardThrust * dirX) + (lateralThrust * perpX);
    double thrustY = (forwardThrust * dirY) + (lateralThrust * perpY);

    double k = 500.0;
    double speedX = myFerry.getSpeedX();
    double speedY = myFerry.getSpeedY();
    double relX = speedX - waterX;
    double relY = speedY - waterY;
    double relMag = std::sqrt(relX * relX + relY * relY);
    double actualDragX = k * relMag * relX;
    double actualDragY = k * relMag * relY;

    double idealMag = std::sqrt(speedX * speedX + speedY * speedY);
    double idealDragX = k * idealMag * speedX;
    double idealDragY = k * idealMag * speedY;

    double ffThrustX = actualDragX - idealDragX;
    double ffThrustY = actualDragY - idealDragY;
    thrustX += ffThrustX;
    thrustY += ffThrustY;
    myFerry.setThrust(thrustX, thrustY);
    lastErrorFwd = errorFwd;
    lastErrorLat = errorLat;

}

bool Controller::isDocked() {
    Position currentPos = myFerry.getPos();
    double errorX = target.x - currentPos.x;
    double errorY = target.y - currentPos.y;
    double distance = std::sqrt(errorX * errorX + errorY * errorY);

    return distance < 10.0;
}
