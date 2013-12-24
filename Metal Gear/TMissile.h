#ifndef TMissile_h
#define TMissile_h

#include "Object.h"
#include "Player.h"

class TMissile : public Object{
    Coordinate finalPos;
    public:
        //Constructor
        TMissile(QWidget *parent = 0, Coordinate finalPos = defaultCoordinate);
        // Move tracking missile
        virtual void moveObject();
        // Converts direction to coordinate
        Coordinate dirToCoor(DIRECTION &dir);
        // Check bounds
        bool boundCheck();
};

#endif