
#ifndef Rocket_h
#define Rocket_h

#include "Projectile.h"

class Rocket: public Projectile{
    public:
        //Constructor
        Rocket(QWidget *parent = 0, Coordinate pos = defaultCoordinate, DIRECTION dir = RIGHT);
        // Move Rocket
        virtual void moveObject();
};

#endif
