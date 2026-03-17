//
// Created by novod on 16.03.2026.
//

#ifndef FERRY_VESSEL_H
#define FERRY_VESSEL_H
#include <cmath>
struct Vector2D {
    double x;
    double y;
    Vector2D operator+(const Vector2D& other) const {
        return{x + other.x, y + other.y};
    }
    Vector2D operator-(const Vector2D other) const {
        return {x - other.x, y - other.y};
    }
    Vector2D operator*(double scalar) const {
        return {x * scalar, y * scalar};
    }
    Vector2D operator/(double scalar) const {
        return{x / scalar, y / scalar};
    }
    double length() const {
        return std::sqrt(x * x + y * y);
    }
    double dot(Vector2D& other) const {
        return x * other.x + y * other.y;
    }
    double cross(Vector2D& other) const {
        return x * other.y - y * other.x;
    }
};

class Vessel {
protected:
    int id;
    double mass;
    Vector2D currentPos;
    double speedX;
    double speedY;
    double currentThrustX;
    double currentThrustY;
    double deltaT;
    double dragCoefficient;
    bool isWaiting;
public:
    Vessel(int index, double m, Vector2D pos, double sx, double sy, double dt, double drag);
    void updatePhysics(double waterX, double waterY);
    int getID() const;
    double getMass() const;
    double getSpeedX() const;
    double getSpeedY() const;
    Vector2D getPos() const;
    bool getWaitStatus();
    void setThrust(double tx, double ty);
    virtual ~Vessel() = default;
};


#endif //FERRY_VESSEL_H