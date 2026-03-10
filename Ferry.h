//
// Created by novod on 09.03.2026.
//

#ifndef FERRY_FERRY_H
#define FERRY_FERRY_H
struct Position {
    double x;
    double y;
};

class Ferry {
private:
    double mass;
    Position currentPos;
    double speedX;
    double speedY;
    double dragCoefficient;
public:
    Ferry(double m, Position startPos, double sx, double sy, double drag);
    Position calcBreakingDist(double waterX, double waterY) const;
    void exportTelemetry(double waterX, double waterY);
    double getMass();
    double getSpeedX() const;
    double getSpeedY() const;
    Position getPos() const;
};


#endif //FERRY_FERRY_H