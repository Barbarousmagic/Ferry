//
// Created by novod on 09.03.2026.
//

#include "Controller.h"
#include <cmath>
#include <algorithm>
Controller::Controller(Vessel& f, Vector2D start, Vector2D t, double kp_value, double ki_value, double kd_value)
    : myVessel(f), startPoint(start), target(t), Kp(kp_value), Ki(ki_value), Kd(kd_value),
        integralFwd(0.0), integralLat(0.0), lastErrorFwd(0.0), lastErrorLat(0.0) {}

void Controller::update(double dt, double waterX, double waterY) {
    Vector2D currentPos = myVessel.getPos();
    Vector2D AB = target - startPoint;
    Vector2D AP = currentPos - startPoint;
    double path_length = AB.length();

    Vector2D unitDirect = AB / path_length;
    Vector2D unitPerp = {-unitDirect.y, unitDirect.x};
    double errorFwd = (target - currentPos).dot(unitDirect);
    double signedCrossProduct = AB.cross(AP);
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
    Vector2D thrust = unitDirect * forwardThrust + unitPerp * lateralThrust;
    double k = 500.0;
    Vector2D speed = {myVessel.getSpeedX(), myVessel.getSpeedY()};
    Vector2D water = {waterX, waterY};
    Vector2D relativeSpeed = speed - water;
    double relMag = relativeSpeed.length();
    Vector2D actualDragForce = relativeSpeed * k * relMag;
    double idealMag = speed.length();
    Vector2D idealDragForce = speed * k * idealMag;
    thrust = thrust + actualDragForce - idealDragForce;
    Ferry* asFerry = dynamic_cast<Ferry*>(&myVessel);
    if (asFerry != nullptr) {
        Ferry* leader = asFerry->getNextFerry();
        if (leader != nullptr) {
            Vector2D nextPos = leader->getPos();
            double distToNext = (currentPos - nextPos).length();
            if (distToNext < 150.0) {
                thrust = {0.0, 0.0};
            }
        }
    }
    double maxThrust = 80000.0;
    thrust = {std::clamp(thrust.x, -maxThrust, maxThrust), std::clamp(thrust.y, -maxThrust, maxThrust)};
    lastErrorFwd = errorFwd;
    lastErrorLat = errorLat;
    myVessel.setThrust(thrust.x, thrust.y);


}

bool Controller::isDocked() {
    return (target - myVessel.getPos()).length() < 20.0;
}
