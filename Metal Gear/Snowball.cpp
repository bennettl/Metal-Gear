
#include "Snowball.h"

//Constructor
Snowball::Snowball(QWidget *parent, Coordinate pos):Object(parent){
    this->image         = new QImage;
    this->image->load(IMAGE_PATH"level3/snowball.png");
    this->rect.setRect(pos.x, pos.y, 10, 10);
}

// Moves the Snowball
void Snowball::moveObject(){
    this->rect.translate(0, TRANSLATE_POINT);
    boundCheck();
}

// Check to see if object is out of bounds
void Snowball::boundCheck(){
    // if it reaches the top end of window, return it to the bottom
    if (this->rect.top() > this->parentWidget()->height() + 100){ 
        this->rect.moveTo(this->rect.x(), 0);
    }
}