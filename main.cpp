#include <iostream>

class Ferry {
public:
    double mass;
    double speed;
    double dragCoefficient;

    double calcBreakingDist(double currentWater) {
        double distanceTraveled = 0.0;
        double dt = 1.0;
        double relativeSpeed = speed - currentWater;
        while (relativeSpeed > 0.1) {
            // 1. Distance traveled in this time step S = V * t
            distanceTraveled += speed * dt;
            // 2. Water drag force F = k * V^2
            double dragForce = dragCoefficient * (relativeSpeed * relativeSpeed);
            // 3. Deceleration a = F / m
            double deceleration = dragForce / mass;
            // 4. Speed update
            speed -= deceleration * dt;
            // 5. Relative Speed for next loop step
            relativeSpeed = speed - currentWater;
        }
        return distanceTraveled;
    }
};



int main() {
    double currentWater;
    Ferry myFerry;
    myFerry.dragCoefficient = 500.0;
    std::cout << "--- IRT Ferry Simulator ---" << std::endl;

    std::cout << "Enter ferry mass (kg): ";
    std::cin >> myFerry.mass;

    while (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Invalid input! Please enter a number for mass (kg): ";
        std::cin >> myFerry.mass;
    }

    std::cout << "Enter start speed (m/s): ";
    std::cin >> myFerry.speed;

    std::cout << "Enter water speed (m/s): ";
    std::cin >> currentWater;

    double resultDistance = myFerry.calcBreakingDist(currentWater);
    std::cout << "\nSuccessfully stopped. Braking distance:" << resultDistance << std::endl;

    return 0;
}