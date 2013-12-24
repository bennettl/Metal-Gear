
#include "Missile.h"

//Constructor
Missile::Missile(QWidget *parent, Coordinate pos):Object(parent){
    this->image = new QImage;
    this->touchedOnce = false;
    this->image->load(IMAGE_PATH"level1/missile.png");
    this->rect.setRect(pos.x, pos.y, 15, 53);
}

// Moves the Missile
void Missile::moveObject(){
    this->rect.translate(0, -TRANSLATE_POINT);
    boundCheck();
}

// Check to see if object is out of bounds
void Missile::boundCheck(){
    // if it reaches the top end of window, return it to the bottom
    if (this->rect.top() < 0){ 
        this->rect.moveTo(this->rect.x(), this->parentWidget()->height() + 50);
    }
}
