
#include "Rocket.h"

// Constructor
Rocket::Rocket(QWidget *parent, Coordinate pos, DIRECTION dir):Projectile(parent){
    this->image  = new QImage;
    QString path;
    path = IMAGE_PATH"projectile/";

    switch (dir) {
        case TOP:
            path += "top/";
            this->rect.setRect(pos.x - 23, pos.y - 10, 12, 31);
            break;
        case RIGHT:
            path += "right/";
            this->rect.setRect(pos.x, pos.y - 5, 33, 12);
            break;
        case BOTTOM:
            path += "bottom/";
            this->rect.setRect(pos.x - 35, pos.y + 2, 12, 31);
            break;
        case LEFT:
            path += "left/";
            this->rect.setRect(pos.x, pos.y - 5, 33, 12);
            break;
        default:
            break;
    }
    path += "rocket.png";
    this->image->load(path);
    this->direction = dir;    
}

// Moves the Rocket
void Rocket::moveObject(){
    // Move the rocket base on direction
    switch (this->direction) {
        case TOP:
            this->rect.translate(0,-TRANSLATE_POINT * 5);
            break;
        case RIGHT:
            this->rect.translate(TRANSLATE_POINT * 5, 0);
            break;
        case BOTTOM:
            this->rect.translate(0,TRANSLATE_POINT * 5);
            break;
        case LEFT:
            this->rect.translate(-TRANSLATE_POINT * 5, 0);
            break;
        default:
            break;
    }
}