
#include "TMissile.h"

//Constructor
TMissile::TMissile(QWidget *parent, Coordinate finalPos):Object(parent){
    QString str;
    // Get a random direction
    DIRECTION dir           = static_cast<DIRECTION>(rand() % BOTTOM_RIGHT);
    Coordinate pos          = dirToCoor(dir);
    this->image             = new QImage();
    this->finalPos.x        = (finalPos.x - pos.x)/45;
    this->finalPos.y        = (finalPos.y - pos.y)/45;    
    str.sprintf(IMAGE_PATH"tmissile/%d.png", dir);
    this->image->load(str);
    this->rect.setRect(pos.x, pos.y, 40, 40);
}

void TMissile::moveObject(){
    // Move horizontal and  vertical
    boundCheck();
    this->rect.translate(finalPos.x,finalPos.y);
}

// If its out of bounds, then reset the position of missile
bool TMissile::boundCheck(){
    int padding = 50;
    if (this->rect.top() < -padding ||  // Top
        this->rect.right() > this->parentWidget()->width() + padding || // Right
        this->rect.bottom() > this->parentWidget()->height() + padding || // Bottom
        this->rect.left() < -padding // Left
        ){
        return true;
    } else {
        return false;
    }
        
}

// Converts direction to coordinate
Coordinate TMissile::dirToCoor(DIRECTION &dir){
    Coordinate pos;
    switch (dir) {
        case TOP_LEFT:
            pos.x = 0;
            pos.y = 0;
            break;
        case TOP_RIGHT:
            pos.x = this->parentWidget()->width();
            pos.y = 0;
            break;
        case BOTTOM_LEFT:
            pos.x = 0;
            pos.y = this->parentWidget()->height();
            break;
        case BOTTOM_RIGHT:
            pos.x = this->parentWidget()->width();
            pos.y = this->parentWidget()->height();
            break;
        default:
            break;
    }
    return pos;
}

