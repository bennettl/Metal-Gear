

#ifndef Soldier_h
#define Soldier_h

#include "Monster.h"

class Soldier : public Monster{
    public:
        //Constructor
        Soldier(QWidget *parent = 0, Coordinate pos = defaultCoordinate);
        // Move Soldier
        virtual void moveObject();
        // Check to see if object is out of bounds
        void boundCheck();
};

#endif
