//
// Created by novod on 09.03.2026.
//

#include "Ferry.h"
#include <cmath>

Ferry::Ferry(double m, double sx, double sy, double drag) {
    mass = m;
    speedX = sx;
    speedY = sy;
    dragCoefficient = drag;
}

double Ferry::getMass() { return mass; }
double Ferry::getSpeedX() { return speedX; }
double Ferry::getSpeedY() { return speedY; }

double Ferry::calcBreakingDist(double waterX, double waterY) {
    double posX = 0.0;
    double posY = 0.0;
    double dt = 1.0;
    double relX = speedX - waterX;
    double relY = speedY - waterY;

    double relMagnitude = std::sqrt(relX * relX + relY * relY);
    while (relMagnitude > 0.1) {
        // 1. Distance traveled in this time step S = V * t
        posX += speedX * dt;
        posY += speedY * dt;
        // 2. Water drag force F = k * V^2
        double dragX = dragCoefficient * (relX * relMagnitude);
        double dragY = dragCoefficient * (relY * relMagnitude);
        // 3. Deceleration a = F / m
        double decX = dragX / mass;
        double decY = dragY / mass;
        // 4. Speed update
        speedX -= decX * dt;
        speedY -= decY * dt;
        // 5. Relative Speed for next loop step
        relX = speedX - waterX;
        relY = speedY - waterY;
        relMagnitude = std::sqrt(relX * relX + relY * relY);
    }
    return std::sqrt(posX * posX + posY * posY);
}


