//
// Created by novod on 09.03.2026.
//

#include "Controller.h"
#include <cmath>
Controller::Controller(Ferry f, Position t) : myFerry(f), target(t) {

}
bool Controller::isDockingSuccessful(double waterX, double waterY) {
    Position finalPos = myFerry.calcBreakingDist(waterX, waterY);
    double missDistance = std::sqrt(std::pow(target.x - finalPos.x, 2) + std::pow(target.y - finalPos.y, 2));
    return missDistance <= 50.0;
}
