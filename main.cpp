#include <iostream>
#include <fstream>
#include <cmath>
#include "Ferry.h"
#include "Controller.h"



int main() {
    double ferryMass;
    double speedX;
    double speedY;
    double waterX;
    double waterY;
    double dt;
    std::cout << "--- IRT Ferry Simulator ---" << std::endl;

    std::cout << "Enter ferry mass (kg): ";
    std::cin >> ferryMass;

    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input! Please enter a number for mass (kg): ";
        std::cin >> ferryMass;
    }

    std::cout << "Enter start speedX (m/s): ";
    std::cin >> speedX;
    std::cout << "Enter start speedY (m/s): ";
    std::cin >> speedY;

    std::cout << "Enter water X-speed (m/s): ";
    std::cin >> waterX;
    std::cout << "Enter water Y-speed (m/s): ";
    std::cin >> waterY;

    std::cout << "Enter time step (s): ";
    std::cin >> dt;

    Position start = {0.0, 0.0};
    Ferry myFerry(ferryMass, start, speedX, speedY, dt, 500.0);
    Position port = {1500.0, 1500.0};
    Controller myAi(myFerry, port, 25.0, 0.5, 0.0);
    std::ofstream file("telemetry.csv");
    file << "Time,PosX,PosY,SpeedX,SpeedY\n";
    double currentTime = 0.0;
    std::cout << "\nStarting simulation..." << std::endl;
    // LOOP
    while (!myAi.isDocked() && currentTime < 5000.0) {
        // 1. Input / AI CONTROL
        myAi.update(dt);
        // 2. UPDATE PHYSICS
        myFerry.updatePhysics(waterX, waterY);
         // 3. LOG
        file << currentTime << ","
             << myFerry.getPos().x << "," << myFerry.getPos().y << ","
             << myFerry.getSpeedX() << "," << myFerry.getSpeedY() << std::endl;
        currentTime += dt;
    }
    if (myAi.isDocked()) {
        std::cout << "SUCCESS: Ferry docked at time " << currentTime << " s!" << std::endl;
    } else {
        std::cout << "WARNING: Time out! Ferry lost at sea." << std::endl;
    }
    file.close();


    return 0;
}