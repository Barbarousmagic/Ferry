//
// Created by novod on 09.03.2026.
//

#include "Ferry.h"
#include <cmath>
#include <fstream>
#include <iostream>

Ferry::Ferry(int index, double m, Position pos, double sx, double sy, double dt, double drag)
    : Vessel(index, m, pos, sx, sy, dt, drag) {
    nextFerry = nullptr;
    currentThrustX = 0.0;
    currentThrustY = 0.0;
}
Ferry* Ferry::getNextFerry() {return nextFerry;}
Position Ferry::calcDist(double waterX, double waterY) const {
    double posX = currentPos.x;
    double posY = currentPos.y;
    double simSpeedX = speedX;
    double simSpeedY = speedY;
    double relX = simSpeedX - waterX;
    double relY = simSpeedY - waterY;
    double simTime = 0.0;
    double relMagnitude = std::sqrt(relX * relX + relY * relY);
    while (relMagnitude > 0.1 && simTime < 1000.0) {
        // 1. Distance traveled in this time step S = V * t
        posX += simSpeedX * deltaT;
        posY += simSpeedY * deltaT;
        // 2. Water drag force F = k * V^2
        double dragX = dragCoefficient * (relX * relMagnitude);
        double dragY = dragCoefficient * (relY * relMagnitude);
        // 3. Adding Thrusting Force
        double forceX = currentThrustX - dragX;
        double forceY = currentThrustY - dragY;
        // 4. Acceleration a = F / m
        double accelX = forceX / mass;
        double accelY = forceY / mass;
        // 5. Speed update
        simSpeedX += accelX * deltaT;
        simSpeedY += accelY * deltaT;
        // 6. Relative Speed for next loop step
        relX = simSpeedX - waterX;
        relY = simSpeedY - waterY;
        relMagnitude = std::sqrt(relX * relX + relY * relY);

        simTime += deltaT;
    }
    Position stopPos;
    stopPos.x = posX;
    stopPos.y = posY;
    return stopPos;
}


void Ferry::setNextFerry(Ferry* next) {
    nextFerry = next;
}