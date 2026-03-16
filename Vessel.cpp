//
// Created by novod on 16.03.2026.
//

#include "Vessel.h"
#include <cmath>
Vessel::Vessel(int index, double m, Position pos, double sx, double sy, double dt, double drag) {
    id = index;
    mass = m;
    currentPos = pos;
    speedX = sx;
    speedY = sy;
    deltaT = dt;
    dragCoefficient = drag;
}
int Vessel::getID() const { return id; }
double Vessel::getMass() const { return mass; }
Position Vessel::getPos() const { return currentPos; }
double Vessel::getSpeedX() const { return speedX; }
double Vessel::getSpeedY() const { return speedY; }
bool Vessel::getWaitStatus() { return isWaiting; }
void Vessel::updatePhysics(double waterX, double waterY) {
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
void Vessel::setThrust(double tx, double ty) {
    currentThrustX = tx;
    currentThrustY = ty;
}