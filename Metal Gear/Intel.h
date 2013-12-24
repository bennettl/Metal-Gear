
#ifndef Intel_h
#define Intel_h

#include "Object.h"

class Intel: public Object{
    public:
        //Constructor
        Intel(QWidget *parent = 0, Coordinate pos = defaultCoordinate);
        // Moves the goal to its current position
        virtual void moveObject();
};

#endif
