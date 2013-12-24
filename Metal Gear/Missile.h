
#ifndef Missle_h
#define Missle_h

#include "Object.h"

class Missile: public Object{
    public:
        //Constructor
        Missile(QWidget *parent = 0, Coordinate pos = defaultCoordinate);
        // Move Missile
        virtual void moveObject();
        // Check to see if object is out of bounds
        void boundCheck();

};

#endif
