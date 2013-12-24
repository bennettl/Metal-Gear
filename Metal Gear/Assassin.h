
#ifndef Assassin_h
#define Assassin_h

#include "LinkedList.h"
#include "Object.h"
#include "Player.h"
#include "Monster.h"

class Assassin : public Monster{
    bool bombhit;
    public:
        //Constructor
        Assassin(QWidget *parent = 0, Coordinate pos = defaultCoordinate);
        // Move Assassin
        virtual void moveObject();
        void moveObject(Linkedlist<Object *> &objectList, Player *player);
        // Update image base on moving direction
        void updateImage();
};

#endif
