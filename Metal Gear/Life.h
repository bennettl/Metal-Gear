
#ifndef Life_h
#define Life_h

#include "Object.h"

class Life: public Object{
    public:
        //Constructor
        Life(QWidget *parent = 0, Coordinate pos = defaultCoordinate);
        // Moves the life item to its current position (static)
        virtual void moveObject();
};


#endif
