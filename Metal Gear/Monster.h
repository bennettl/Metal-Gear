
#ifndef Monster_h
#define Monster_h

#include "Object.h"

class Monster: public Object{
    protected:
        bool walking;
    public:
        //Constructor
        Monster(QWidget *parent = 0);
};

#endif
