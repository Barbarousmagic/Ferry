#include <iostream>

int main() {
    double ferryMass; // kg
    double currentSpeed; // m/s
    double dragCoefficient = 0.04;

    std::cout << "Enter ferry mass (kg):" << std::endl;
    std::cin >> ferryMass;

    std::cout << "Enter start speed (m/s):" << std::endl;
    std::cin >> currentSpeed;

    // Physics simulation variables
    double distanceTraveled = 0.0; // meters
    double dt = 1.0; // delta t in seconds


    while (currentSpeed > 0.1) {
        // 1. Distance traveled in this time step S = V * t
        distanceTraveled += currentSpeed * dt;

        // 2. Water drag force F = k * V^2
        double dragForce = dragCoefficient * (currentSpeed * currentSpeed);

        // 3. Deceleration a = F / m
        double deceleration = dragForce / ferryMass;

        // 4. Speed update
        currentSpeed -= deceleration * dt;

        std::cout << "Current speed: " << currentSpeed << "m/s | Distance:" << distanceTraveled<< "m" << std::endl;
    }

    std::cout << "\nSuccessfully stopped. Braking distance:" << distanceTraveled << std::endl;

    return 0;
}