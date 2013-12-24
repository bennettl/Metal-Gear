
#ifndef Snowball_h
#define Snowball_h

#include "Object.h"

class Snowball: public Object{
    public:
        //Constructor
        Snowball(QWidget *parent = 0, Coordinate pos = defaultCoordinate);
        // Move snowball
        virtual void moveObject();
        // Check to see if object is out of bounds
        void boundCheck();  
};

#endif