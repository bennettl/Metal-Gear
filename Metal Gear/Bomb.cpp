
#include "Bomb.h"

//Constructor
Bomb::Bomb(QWidget *parent, Coordinate pos):Object(parent){
    this->image = new QImage;
    this->image->load(IMAGE_PATH"level1/bomb.png");
    this->rect.setRect(pos.x, pos.y, 20, 20);
}

// Moves the bomb to its current position (static)
void Bomb::moveObject(){
    return;
}
