//
// Created by novod on 09.03.2026.
//

#include "Ferry.h"
#include <cmath>
#include <fstream>
#include <iostream>

Ferry::Ferry(int index, double m, Position startPos, double sx, double sy, double dt, double drag) {
    id = index;
    nextFerry = nullptr;
    isWaiting = true;
    mass = m;
    currentPos = startPos;
    speedX = sx;
    speedY = sy;
    currentThrustX = 0.0;
    currentThrustY = 0.0;
    deltaT = dt;
    dragCoefficient = drag;
}

int Ferry::getID() {return id;}
Ferry* Ferry::getNextFerry() {return nextFerry;}
bool Ferry::getWaitStatus() { return isWaiting;}
double Ferry::getMass() { return mass; }
Position Ferry::getPos() const { return currentPos; }
double Ferry::getSpeedX() const { return speedX; }
double Ferry::getSpeedY() const { return speedY; }


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

void Ferry::updatePhysics(double waterX, double waterY) {
    double relX = speedX - waterX;
    double relY = speedY - waterY;
    double relMagnitude = std::sqrt(relX * relX + relY * relY);
    currentPos.x += speedX * deltaT;
    currentPos.y += speedY * deltaT;
    double dragX = dragCoefficient * (relMagnitude * relX);
    double dragY = dragCoefficient * (relMagnitude * relY);
    double forceX = currentThrustX - dragX;
    double forceY = currentThrustY - dragY;
    double accelX = forceX / mass;
    double accelY = forceY / mass;
    speedX += accelX * deltaT;
    speedY += accelY * deltaT;
}

void Ferry::setThrust(double tx, double ty) {
    currentThrustX = tx;
    currentThrustY = ty;
}

void Ferry::setNextFerry(Ferry* next) {
    nextFerry = next;
}