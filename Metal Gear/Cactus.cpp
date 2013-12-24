
#include "Cactus.h"

//Constructor
Cactus::Cactus(QWidget *parent, Coordinate pos):Object(parent){
    this->image = new QImage;
    this->image->load(IMAGE_PATH"level2/cactus.png");
    this->rect.setRect(pos.x, pos.y, 45, 85);
}

// Moves the life item to its current position (static)
void Cactus::moveObject(){
    return;
}