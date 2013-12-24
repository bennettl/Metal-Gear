
#ifndef Icespike_h
#define Icespike_h

#include "Object.h"

class Icespike : public Object{
    Coordinate finalPos;
    public:
        //Constructor
        Icespike(QWidget *parent = 0, Coordinate startPos = defaultCoordinate);
        // Move icespike
        virtual void moveObject();
        // Check bounds
        bool boundCheck();
};

#endif
