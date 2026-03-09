//
// Created by novod on 09.03.2026.
//

#ifndef FERRY_FERRY_H
#define FERRY_FERRY_H


class Ferry {
private:
    double mass;
    double speed;
    double dragCoefficient;
public:
    Ferry(double m, double s, double drag);
    double calcBreakingDist(double currentWater);
};


#endif //FERRY_FERRY_H