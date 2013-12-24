
#include "Rock.h"

//Constructor
Rock::Rock(QWidget *parent, Coordinate pos):Object(parent){
    this->image = new QImage;
    int random  = (rand() % 100);
    // Set the image randomly
    if (random > 50){
        this->rect.setRect(pos.x, pos.y, 58, 32);
        this->image->load(IMAGE_PATH"level3/rock.png");
        
    } else {
        this->rect.setRect(pos.x, pos.y, 42, 32);
        this->image->load(IMAGE_PATH"level3/rock1.png");
    }
}

// Moves the bomb to its current position (static)
void Rock::moveObject(){
    return;
}
