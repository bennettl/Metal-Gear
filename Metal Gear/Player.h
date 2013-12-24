#ifndef Player_h
#define Player_h

#include "Object.h"
#include "LinkedList.h"

class Player: public Object{
    WEAPON weapon;
    bool hidden, walking;
    public:
        //Constructor
        Player(QWidget *parent = 0, Coordinate pos = defaultCoordinate);
        // Returns hidden status
        bool getHidden();
        // Returns direction
        DIRECTION getDirection();
        // Returns weapon
        WEAPON getWeapon();
        // Determine if player had collided with another object
        bool isCollided(int &index, Linkedlist<Object *> &objectList);
        // Does not move the object, but has to implement it because it inherits from Object class
        virtual void moveObject();  
        // Moves the player
        void keyMoveObject(int input);
        // Make sure the player stays in bounds
        void boundCheck();

};

#endif