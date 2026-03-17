//
// Created by novod on 16.03.2026.
//

#include "Vessel.h"
#include <cmath>
Vessel::Vessel(int index, double m, Vector2D pos, double sx, double sy, double dt, double drag) {
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
Vector2D Vessel::getPos() const { return currentPos; }
double Vessel::getSpeedX() const { return speedX; }
double Vessel::getSpeedY() const { return speedY; }
bool Vessel::getWaitStatus() { return isWaiting; }
void Vessel::updatePhysics(double waterX, double waterY) {
    Vector2D speed = {speedX, speedY};
    Vector2D water = {waterX, waterY};
    Vector2D thrust = {currentThrustX, currentThrustY};
    Vector2D relVelocity = speed - water;
    double relMagnitude = relVelocity.length();
    currentPos = currentPos + speed * deltaT;
    Vector2D dragForce = relVelocity * dragCoefficient * relMagnitude;
    Vector2D totalForce = thrust - dragForce;
    Vector2D acceleration = totalForce * (1.0 / mass);
    speed = speed + acceleration * deltaT;
    speedX = speed.x;
    speedY = speed.y;
}
void Vessel::setThrust(double tx, double ty) {
    currentThrustX = tx;
    currentThrustY = ty;
}