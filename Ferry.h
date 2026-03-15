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
    int id;
    Ferry* nextFerry;
    bool isWaiting;
    double mass;
    Position currentPos;
    double speedX;
    double speedY;
    double currentThrustX;
    double currentThrustY;
    double deltaT;
    double dragCoefficient;
public:
    Ferry(int id, double m, Position startPos, double sx, double sy, double dt, double drag);
    Position calcDist(double waterX, double waterY) const;
    void updatePhysics(double waterX, double waterY);
    int getID();
    Ferry* getNextFerry ();
    bool getWaitStatus ();
    double getMass();
    double getSpeedX() const;
    double getSpeedY() const;
    Position getPos() const;
    void setThrust(double tx, double ty);

    void setNextFerry(Ferry* next);
};


#endif //FERRY_FERRY_H