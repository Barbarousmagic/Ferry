#include <iostream>
#include "Ferry.h"



int main() {
    double currentWater;
    double ferryMass;
    double currentSpeed;
    std::cout << "--- IRT Ferry Simulator ---" << std::endl;

    std::cout << "Enter ferry mass (kg): ";
    std::cin >> ferryMass;

    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input! Please enter a number for mass (kg): ";
        std::cin >> ferryMass;
    }

    std::cout << "Enter start speed (m/s): ";
    std::cin >> currentSpeed;

    std::cout << "Enter water speed (m/s): ";
    std::cin >> currentWater;

    Ferry myFerry(ferryMass, currentSpeed, 500.0);
    double resultDistance = myFerry.calcBreakingDist(currentWater);
    std::cout << "\nSuccessfully stopped. Braking distance:" << resultDistance << std::endl;
    std::cout << "Ferry mass is: " << myFerry.getMass() << " kg" << std::endl;
    return 0;
}