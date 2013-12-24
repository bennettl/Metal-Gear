
#include <QtGui/qevent.h>
#include <QtGui/qpainter.h>
#include "Bullet.h"

// Constructor
Bullet::Bullet(QWidget *parent, Coordinate pos, DIRECTION dir):Projectile(parent){
    this->image  = new QImage;
    QString path;
    path = IMAGE_PATH"projectile/";
    
    switch (dir) {
        case TOP:
            path += "top/";
            this->rect.setRect(pos.x - 23, pos.y - 10, 8, 24);
            break;
        case RIGHT:
            path += "right/";
            this->rect.setRect(pos.x, pos.y, 30, 8);
            break;
        case BOTTOM:
            path += "bottom/";
            this->rect.setRect(pos.x - 30, pos.y + 2, 8, 24);
            break;
        case LEFT:
            path += "left/";
            this->rect.setRect(pos.x, pos.y, 30, 8);
            break;
        default:
            break;
    }
    path += "bullet.png";
    this->image->load(path);
    this->direction = dir;
}

// Moves the bullet
void Bullet::moveObject(){    
    // Move the butlet base on direction
    switch (this->direction) {
        case TOP:
            this->rect.translate(0,-TRANSLATE_POINT * 3);
            break;
        case RIGHT:
            this->rect.translate(TRANSLATE_POINT * 3, 0);
            break;
        case BOTTOM:
            this->rect.translate(0,TRANSLATE_POINT * 3);
            break;
        case LEFT:
            this->rect.translate(-TRANSLATE_POINT * 3, 0);
            break;
        default:
            break;
    }
}