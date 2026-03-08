#include <iostream>

double calcBreakingDist(double mass, double speed, double dragCoeff) {
    double distanceTraveled = 0.0;
    double dt = 1.0;
    while (speed > 0.1) {
        // 1. Distance traveled in this time step S = V * t
        distanceTraveled += speed * dt;
        // 2. Water drag force F = k * V^2
        double dragForce = dragCoeff * (speed * speed);
        // 3. Deceleration a = F / m
        double deceleration = dragForce / mass;
        // 4. Speed update
        speed -= deceleration * dt;
    }
    return distanceTraveled;
}

int main() {
    double ferryMass; // kg
    double currentSpeed; // m/s
    double dragCoefficient = 500.0;

    std::cout << "--- IRT Ferry Simulator ---" << std::endl;

    std::cout << "Enter ferry mass (kg): ";
    std::cin >> ferryMass;

    std::cout << "Enter start speed (m/s): ";
    std::cin >> currentSpeed;

    double resultDistance = calcBreakingDist(ferryMass, currentSpeed, dragCoefficient);
    std::cout << "\nSuccessfully stopped. Braking distance:" << resultDistance << std::endl;

    return 0;
}