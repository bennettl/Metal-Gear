
#ifndef Cactus_h
#define Cactus_h

#include "Object.h"

class Cactus: public Object{
    public:
        //Constructor
        Cactus(QWidget *parent = 0, Coordinate pos = defaultCoordinate);
        // Moves the life item to its current position (static)
        virtual void moveObject();
};

#endif
