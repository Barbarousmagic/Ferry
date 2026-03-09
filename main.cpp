#include <iostream>

double calcBreakingDist(double mass, double speed, double currentWater, double dragCoeff) {
    double distanceTraveled = 0.0;
    double dt = 1.0;
    double relativeSpeed = speed - currentWater;
    while (relativeSpeed > 0.1) {
        // 1. Distance traveled in this time step S = V * t
        distanceTraveled += speed * dt;
        // 2. Water drag force F = k * V^2
        double dragForce = dragCoeff * (relativeSpeed * relativeSpeed);
        // 3. Deceleration a = F / m
        double deceleration = dragForce / mass;
        // 4. Speed update
        speed -= deceleration * dt;
        // 5. Relative Speed for next loop step
        relativeSpeed = speed - currentWater;
    }
    return distanceTraveled;
}

int main() {
    double ferryMass; // kg
    double currentSpeed; // m/s
    double currentWater;
    double dragCoefficient = 500.0;

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

    double resultDistance = calcBreakingDist(ferryMass, currentSpeed, currentWater, dragCoefficient);
    std::cout << "\nSuccessfully stopped. Braking distance:" << resultDistance << std::endl;

    return 0;
}