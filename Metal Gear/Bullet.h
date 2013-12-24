
#ifndef Bullet_h
#define Bullet_h

#include "Projectile.h"

class Bullet : public Projectile{
    public:
        //Constructor
        Bullet(QWidget *parent = 0, Coordinate pos = defaultCoordinate, DIRECTION dir = RIGHT);
        // Move bullet
        virtual void moveObject();
};

#endif
