
#include "Scorpion.h"

//Constructor
Scorpion::Scorpion(QWidget *parent, Coordinate pos):Monster(parent){
    this->image             = new QImage;
    this->direction         = RIGHT;
    this->touchedOnce       = false;
    this->image->load(IMAGE_PATH"level2/monsterRight.png");
    this->rect.setRect(pos.x, pos.y, 70, 35);
}

// Moves the Scorpion
void Scorpion::moveObject(){
    // If it turns right, increment the column and set the approriate symbol
    if (this->direction == RIGHT){
        this->rect.translate(TRANSLATE_POINT, 0);
        boundCheck();
    } else {
        this->rect.translate(-TRANSLATE_POINT, 0);
        boundCheck();
    }
}

// Check to see if object is out of bounds
void Scorpion::boundCheck(){
    // if it reaches the right end of window, set turn right equal to false.
    // If it reaches the left end of window, set turnRight equal to true
    if (this->rect.right() >= this->parentWidget()->width()){ 
        this->rect.translate(-TRANSLATE_POINT, 0);
        this->direction    = LEFT;
        this->image->load(IMAGE_PATH"level2/monsterLeft.png");
    } else if (this->rect.left() <= 0){
        this->rect.translate(TRANSLATE_POINT, 0);
        this->direction    = RIGHT;
        this->image->load(IMAGE_PATH"level2/monsterRight.png");
    }
}
