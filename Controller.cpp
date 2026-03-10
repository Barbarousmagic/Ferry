//
// Created by novod on 09.03.2026.
//

#include "Controller.h"
#include <cmath>
Controller::Controller(Ferry f, double tX, double tY) : myFerry(f), targetX(tX), targetY(tY) {

}
bool Controller::checkCollision(double waterX, double waterY) {
    double currentX = myFerry.getPosX();
    double currentY = myFerry.getPosY();
    double waypointDist = std::sqrt(std::pow(targetX - currentX, 2) + std::pow(targetY - currentY, 2));
    return myFerry.calcBreakingDist(waterX, waterY) >= waypointDist;
}
