#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <memory>
#include "Ferry.h"
#include "Controller.h"



int main() {
    double ferryMass = 15000.0;
    double speedX = 0.0;
    double speedY = 0.0;
    double waterX = -2.0;
    double waterY = -5.0;
    double dt = 0.1;
    std::cout << "--- IRT Ferry Simulator ---" << std::endl;

    /*std::cout << "Enter ferry mass (kg): ";
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
    std::cin >> dt;*/

    std::vector<std::unique_ptr<Ferry>> fleet;
    std::vector<std::unique_ptr<Controller>> ais;
    Position port = {1500.0, 5000.0};
    for (int i = 0; i < 5; i++) {
        Position start = {500.0 * i, 0};
        fleet.push_back(std::make_unique<Ferry>(i, ferryMass, start, speedX, speedY, dt, 500.0));
        if (i > 0) {fleet[i]->setNextFerry(fleet[i-1].get());}
        ais.push_back(std::make_unique<Controller>(*fleet[i], start, port, 500.0, 1.0, 5000.0));
    }
    std::ofstream file("telemetry.csv");
    file << "Time,FerryID,PosX,PosY,SpeedX,SpeedY\n";
    double currentTime = 0.0;
    std::cout << "\nStarting simulation..." << std::endl;
    // LOOP
    while (currentTime < 1000.0) {
        bool allDocked = true;
        for (int i = 0; i < fleet.size(); i++) {
            // 1. Input / AI CONTROL
            ais[i]->update(dt, waterX, waterY);
            // 2. UPDATE PHYSICS
            fleet[i]->updatePhysics(waterX, waterY);
            // 3. LOG
            Position pos = fleet[i]->getPos();
            file << currentTime << "," << fleet[i]->getID() << ","
                 << pos.x << "," << pos.y << ","
                 << fleet[i]->getSpeedX() << "," << fleet[i]->getSpeedY() << std::endl;
            double distToPort = std::sqrt(std::pow(pos.x - port.x, 2) + std::pow(pos.y - port.y, 2));
            if (distToPort > 10.0) allDocked = false;
        }
        if (!ais.empty() && ais[0]->isDocked()) {
            ais.erase(ais.begin());
            fleet.erase(fleet.begin());
            if (!fleet.empty())  { fleet[0]->setNextFerry(nullptr); }
        }
        if (std::fmod(currentTime, 100.0) < dt) {
            std::cout << "Simulating... Time: " << currentTime << "s" << std::endl;
        }
        if (allDocked) {
            std::cout << "SUCCESS: All ferries docked at port at time " << currentTime << "s!" << std::endl;
            break;
        }
        currentTime += dt;
    }
    file.close();
    return 0;
}