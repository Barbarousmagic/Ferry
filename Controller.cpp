//
// Created by novod on 09.03.2026.
//

#include "Controller.h"

Controller::Controller(Ferry f, double dist) : myFerry(f), distanceToTarget(dist) {

}
bool Controller::checkCollision(double waterX, double waterY) {
    return myFerry.calcBreakingDist(waterX, waterY) >= distanceToTarget;
}
