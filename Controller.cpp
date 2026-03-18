//
// Created by novod on 09.03.2026.
//

#include "Controller.h"
#include <cmath>
#include <algorithm>
Controller::Controller(Vessel& f, Vector2D start, Vector2D t, double kp_value, double ki_value, double kd_value)
    : myVessel(f), startPoint(start), target(t), Kp(kp_value), Ki(ki_value), Kd(kd_value),
        integralFwd(0.0), integralLat(0.0) {}

void Controller::update(double dt, double waterX, double waterY) {
    Vector2D currentPos = myVessel.getPos();
    Vector2D speed = {myVessel.getSpeedX(), myVessel.getSpeedY()};
    Vector2D water = {waterX, waterY};
    Vector2D AB = target - startPoint;
    Vector2D AP = currentPos - startPoint;
    double path_length = AB.length();

    Vector2D unitDirect = AB / path_length;
    Vector2D unitPerp = {-unitDirect.y, unitDirect.x};
    double errorFwd = (target - currentPos).dot(unitDirect);

    // ---ADAPTIVE CRUISE CONTROL (ACC)----
    Ferry* asFerry = dynamic_cast<Ferry*>(&myVessel);
    if (asFerry != nullptr) {
        Ferry* leader = asFerry->getNextFerry();
        if (leader != nullptr) {
            Vector2D nextPos = leader->getPos();
            double distToLeaderFwd = (nextPos - currentPos).dot(unitDirect);
            double safeDist = 150.0;
            double allowedErrorFwd = distToLeaderFwd - safeDist;
            if (allowedErrorFwd < errorFwd) errorFwd = allowedErrorFwd;
        }
    }
    double signedCrossProduct = AB.cross(AP);
    double errorLat = signedCrossProduct / path_length; // XTE
    double integrationZoneFwd = 50.0;
    if (std::abs(errorFwd) < integrationZoneFwd) integralFwd += errorFwd * dt;
    else integralFwd = 0.0;
    double integrationZoneLat = 20.0;
    if (std::abs(errorLat) < integrationZoneLat) integralLat += errorLat * dt;
    else integralLat = 0.0;

    double derivFwd = - speed.dot(unitDirect);
    double derivLat = - speed.dot(unitPerp);
    double forwardThrust = Kp * errorFwd + Ki * integralFwd + Kd * derivFwd;
    double lateralThrust = 15 * Kp * (-errorLat) + Ki * (-integralLat) + 15 * Kd * derivLat;
    Vector2D thrust = unitDirect * forwardThrust + unitPerp * lateralThrust;
    double k = 500.0;

    Vector2D relativeSpeed = speed - water;
    double relMag = relativeSpeed.length();
    Vector2D actualDragForce = relativeSpeed * k * relMag;
    double idealMag = speed.length();
    Vector2D idealDragForce = speed * k * idealMag;
    thrust = thrust + actualDragForce - idealDragForce;
    double maxThrust = 80000.0;
    double thrustMag = thrust.length();
    if (thrustMag > maxThrust) thrust = (thrust / thrustMag) * maxThrust;
    myVessel.setThrust(thrust.x, thrust.y);


}

bool Controller::isDocked() {
    return (target - myVessel.getPos()).length() < 20.0;
}
