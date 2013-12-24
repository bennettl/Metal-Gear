
#ifndef Scorpion_h
#define Scorpion_h

#include "Monster.h"

class Scorpion: public Monster{
    public:
        //Constructor
        Scorpion(QWidget *parent = 0, Coordinate pos = defaultCoordinate);
        // Move Scorpion
        virtual void moveObject();
        // Check to see if object is out of bounds
        void boundCheck();
};


#endif
