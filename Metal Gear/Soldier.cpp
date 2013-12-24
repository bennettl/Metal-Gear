
#include "Soldier.h"

//Constructor
Soldier::Soldier(QWidget *parent, Coordinate pos):Monster(parent){
    this->image             = new QImage;
    this->direction         = RIGHT;
    this->touchedOnce       = false;
    this->image->load(IMAGE_PATH"level1/monsterRight.png");
    this->rect.setRect(pos.x, pos.y, 30, 47);
}

// Moves the Soldier
void Soldier::moveObject(){
    this->walking = !this->walking;

    // If it turns right, increment the column and set the approriate symbol
    if (this->direction == RIGHT){
        this->rect.translate(TRANSLATE_POINT, 0);
    } else {
        this->rect.translate(-TRANSLATE_POINT, 0);
    }
    boundCheck();
}

// Check to see if object is out of bounds
void Soldier::boundCheck(){
    // if it reaches the right end of window, set turn right equal to false.
    // If it reaches the left end of window, set turnRight equal to true
    if (this->rect.right() >= this->parentWidget()->width()){ 
        this->rect.translate(-TRANSLATE_POINT, 0);
        this->direction    = LEFT;
        this->image->load(IMAGE_PATH"level1/monsterLeft.png");
    } else if (this->rect.left() <= 0){
        this->rect.translate(TRANSLATE_POINT, 0);
        this->direction    = RIGHT;
        this->image->load(IMAGE_PATH"level1/monsterRight.png");
    }
}
