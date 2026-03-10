//
// Created by novod on 09.03.2026.
//

#include "Ferry.h"
#include <cmath>
#include <fstream>
#include <iostream>

Ferry::Ferry(double m, double x, double y, double sx, double sy, double drag) {
    mass = m;
    posX = x;
    posY = y;
    speedX = sx;
    speedY = sy;
    dragCoefficient = drag;
}

double Ferry::getMass() { return mass; }

double Ferry::getPosX() const {return posX;}
double Ferry::getPosY() const {return posY;}
double Ferry::getSpeedX() const { return speedX; }
double Ferry::getSpeedY() const { return speedY; }

double Ferry::calcBreakingDist(double waterX, double waterY) const {
    double posX = 0.0;
    double posY = 0.0;
    double dt = 1.0;
    double simSpeedX = speedX;
    double simSpeedY = speedY;
    double relX = simSpeedX - waterX;
    double relY = simSpeedY - waterY;

    double relMagnitude = std::sqrt(relX * relX + relY * relY);
    while (relMagnitude > 0.1) {
        // 1. Distance traveled in this time step S = V * t
        posX += simSpeedX * dt;
        posY += simSpeedY * dt;
        // 2. Water drag force F = k * V^2
        double dragX = dragCoefficient * (relX * relMagnitude);
        double dragY = dragCoefficient * (relY * relMagnitude);
        // 3. Deceleration a = F / m
        double decX = dragX / mass;
        double decY = dragY / mass;
        // 4. Speed update
        simSpeedX -= decX * dt;
        simSpeedY -= decY * dt;
        // 5. Relative Speed for next loop step
        relX = simSpeedX - waterX;
        relY = simSpeedY - waterY;
        relMagnitude = std::sqrt(relX * relX + relY * relY);
    }
    return std::sqrt(posX * posX + posY * posY);
}

void Ferry::exportTelemetry(double waterX, double waterY) {
    std::ofstream file("telemetry.csv");
    if (!file.is_open()) {
        std::cout << "Error: File cannot be open" << std::endl;
        return;
    }
    file << "Time,PosX,PosY,SpeedX,SpeedY\n";

    double posX = 0.0;
    double posY = 0.0;
    double currentTime = 0.0;
    double dt = 1.0;
    double simSpeedX = speedX;
    double simSpeedY = speedY;
    double relX = simSpeedX - waterX;
    double relY = simSpeedY - waterY;

    double relMagnitude = std::sqrt(relX * relX + relY * relY);
    while (relMagnitude > 0.1) {
        file << currentTime << "," << posX << "," << posY << "," << simSpeedX << "," << simSpeedY << std::endl;
        posX += simSpeedX * dt;
        posY += simSpeedY * dt;

        double dragX = dragCoefficient * (relX * relMagnitude);
        double dragY = dragCoefficient * (relY * relMagnitude);

        double decX = dragX / mass;
        double decY = dragY / mass;

        simSpeedX -= decX * dt;
        simSpeedY -= decY * dt;

        relX = simSpeedX - waterX;
        relY = simSpeedY - waterY;
        relMagnitude = std::sqrt(relX * relX + relY * relY);

        currentTime += dt;
    }
    file.close();

}
