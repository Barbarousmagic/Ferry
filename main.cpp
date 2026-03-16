#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <memory>
#include "Ferry.h"
#include "Controller.h"
#include "Speedboat.h"


int main() {
    double ferryMass;
    double speedBoatMass;
    double speedX;
    double speedY;
    double waterX;
    double waterY;
    double dt;
    std::ifstream configFile("config.txt");
    if (!configFile.is_open()) {
        std::cerr << "Error: config.txt not found" << std::endl;
        return 1;
    }
    std::string key;
    double value;
    std::vector<std::string> shipTypes;
    while (configFile >> key) {
        if (key == "ferryMass") configFile >> ferryMass;
        else if (key == "speedBoatMass") configFile >> speedBoatMass;
        else if (key == "speedX") configFile >> speedX;
        else if (key == "speedY") configFile >> speedY;
        else if (key == "waterX") configFile >> waterX;
        else if (key == "waterY") configFile >> waterY;
        else if (key == "dt") configFile >> dt;
        else if (key == "ship") {
            std::string type;
            configFile >> type;
            shipTypes.push_back(type);
        }
    }
    configFile.close();
    std::cout << "--- IRT Ferry Simulator ---" << std::endl;
    std::vector<std::unique_ptr<Vessel>> fleet;
    std::vector<std::unique_ptr<Controller>> ais;
    Position port = {1500.0, 5000.0};
    for (int i = 0; i < shipTypes.size(); i++) {
        Position start = {500.0 * i, 0};
        if (shipTypes[i] == "Speedboat") {
            fleet.push_back(std::make_unique<Speedboat>(i, speedBoatMass, start, speedX, speedY, dt, 100.0));
        }
        else if (shipTypes[i] == "Ferry"){
            fleet.push_back(std::make_unique<Ferry>(i, ferryMass, start, speedX, speedY, dt, 500.0));
        }
        if (i > 0) {
            Ferry* currFerry = dynamic_cast<Ferry*>(fleet[i].get());
            Ferry* prevFerry = dynamic_cast<Ferry*>(fleet[i-1].get());
            if (currFerry && prevFerry) {
                currFerry->setNextFerry(prevFerry);
            }
        }
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
        for (int i = 0; i < ais.size(); ) {
            if (ais[i]->isDocked()) {
                ais.erase(ais.begin() + i);
                fleet.erase(fleet.begin() + i);
                if (i == 0 && !fleet.empty()) {
                    Ferry* currFerry = dynamic_cast<Ferry*>(fleet[0].get());
                    if (currFerry) currFerry->setNextFerry(nullptr);
                }
            }
            else i++;
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
    if (!fleet.empty()) std::cout << "TIMEOUT: Simulation ended but " << fleet.size() << " vessels are still at sea" << std::endl;
    file.close();
    return 0;
}