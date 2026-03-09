//
// Created by novod on 09.03.2026.
//

#include "Ferry.h"

Ferry::Ferry(double m, double s, double drag) {
    mass = m;
    speed = s;
    dragCoefficient = drag;
}

double Ferry::calcBreakingDist(double currentWater) {
    double distanceTraveled = 0.0;
    double dt = 1.0;
    double relativeSpeed = speed - currentWater;
    while (relativeSpeed > 0.1) {
        // 1. Distance traveled in this time step S = V * t
        distanceTraveled += speed * dt;
        // 2. Water drag force F = k * V^2
        double dragForce = dragCoefficient * (relativeSpeed * relativeSpeed);
        // 3. Deceleration a = F / m
        double deceleration = dragForce / mass;
        // 4. Speed update
        speed -= deceleration * dt;
        // 5. Relative Speed for next loop step
        relativeSpeed = speed - currentWater;
    }
    return distanceTraveled;
}

double Ferry::getMass() {
    return mass;
}

double Ferry::getSpeed() {
    return speed;
}
