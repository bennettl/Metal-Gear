
#ifndef Bomb_h
#define Bomb_h

#include "Object.h"

class Bomb: public Object{
    public:
        //Constructor
        Bomb(QWidget *parent = 0, Coordinate pos = defaultCoordinate);
        // Moves the bomb item to its current position (static)
        virtual void moveObject();
};

#endif