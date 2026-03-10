//
// Created by novod on 09.03.2026.
//

#ifndef FERRY_FERRY_H
#define FERRY_FERRY_H


class Ferry {
private:
    double mass;
    double posX;
    double posY;
    double speedX;
    double speedY;
    double dragCoefficient;
public:
    Ferry(double m, double x, double y, double sx, double sy, double drag);
    double calcBreakingDist(double waterX, double waterY) const;
    void exportTelemetry(double waterX, double waterY);
    double getMass();
    double getSpeedX() const;
    double getSpeedY() const;
    double getPosX() const;
    double getPosY() const;
};


#endif //FERRY_FERRY_H