//
// Created by novod on 09.03.2026.
//

#ifndef FERRY_FERRY_H
#define FERRY_FERRY_H


class Ferry {
private:
    double mass;
    double speedX;
    double speedY;
    double dragCoefficient;
public:
    Ferry(double m, double sx, double sy, double drag);
    double calcBreakingDist(double waterX, double waterY) const;
    void exportTelemetry(double waterX, double waterY);
    double getMass();
    double getSpeedX();
    double getSpeedY();
};


#endif //FERRY_FERRY_H