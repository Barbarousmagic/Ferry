#include <iostream>
#include "Ferry.h"



int main() {
    double ferryMass;
    double speedX;
    double speedY;
    double waterX;
    double waterY;
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

    Ferry myFerry(ferryMass, speedX, speedY, 500.0);
    double resultDistance = myFerry.calcBreakingDist(waterX, waterY);
    std::cout << "\nSuccessfully stopped. Braking distance:" << resultDistance << std::endl;
    std::cout << "Ferry mass is: " << myFerry.getMass() << " kg" << std::endl;
    return 0;
}