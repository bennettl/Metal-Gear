
#ifndef Rock_h
#define Rock_h

#include "Object.h"

class Rock : public Object{
    public:
        //Constructor
        Rock(QWidget *parent = 0, Coordinate pos = defaultCoordinate);
        // Moves the bomb item to its current position (static)
        virtual void moveObject();
};

#endif
