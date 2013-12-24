#include "Object.h"

QImage* Object::getImage(){
    return this->image;
}

QRect Object::getRect(){
    return this->rect;
}

bool Object::getTouchedOnce(){
    return this->touchedOnce;
}

// Set the position of the rect
void Object::setPosition(int x, int y){
    this->rect.moveTo(x,y);
}

void Object::setTouchedOnce(bool value){
    this->touchedOnce = value;
}

// Destructor
Object::~Object(){
    delete this->image;
}