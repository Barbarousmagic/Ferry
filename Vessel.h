//
// Created by novod on 16.03.2026.
//

#ifndef FERRY_VESSEL_H
#define FERRY_VESSEL_H
struct Position {
    double x;
    double y;
};

class Vessel {
protected:
    int id;
    double mass;
    Position currentPos;
    double speedX;
    double speedY;
    double currentThrustX;
    double currentThrustY;
    double deltaT;
    double dragCoefficient;
    bool isWaiting;
public:
    Vessel(int index, double m, Position pos, double sx, double sy, double dt, double drag);
    void updatePhysics(double waterX, double waterY);
    int getID() const;
    double getMass() const;
    double getSpeedX() const;
    double getSpeedY() const;
    Position getPos() const;
    bool getWaitStatus();
    void setThrust(double tx, double ty);
    virtual ~Vessel() = default;
};


#endif //FERRY_VESSEL_H