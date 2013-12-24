#include "Player.h"

//Constructor
Player::Player(QWidget *parent, Coordinate pos):Object(parent){
    this->image     = new QImage;
    this->direction = RIGHT;
    this->hidden    = false;
    this->walking   = false;
    this->weapon    = PISTOL;
    this->image->load(IMAGE_PATH"player/right/pistol0.png");
    this->rect.setRect(pos.x, pos.y, 45, 45);
}

// Returns hidden status
bool Player::getHidden(){
    return this->hidden;
}

// Returns direction
DIRECTION Player::getDirection(){
    return this->direction;
}

// Returns weapon
WEAPON Player::getWeapon(){
    return this->weapon;
}

// Determine if player has collided with another object
bool Player::isCollided(int &index, Linkedlist<Object *> &objectList){
    for (int i = 0; i < objectList.size(); i++) {
        Object *obj = objectList.at(i);
        if ((this->rect.intersects(obj->getRect())) && !(dynamic_cast<Player *>(obj))){
            index = i;
            return true;
        } else {
            obj->setTouchedOnce(false);
        }
    }
    return false;
}

void Player::moveObject(){
    return;
}

// Moves the player
void Player::keyMoveObject(int input){
    this->hidden  = false;
    switch (input) {
        case Qt::Key_W: 
            this->direction = TOP;
            this->rect.translate(0, -TRANSLATE_POINT * 2);
            break;
        case Qt::Key_A:  
            this->direction = LEFT;
            this->walking = !this->walking;
            this->rect.translate(-TRANSLATE_POINT * 2, 0);
            break;
        case Qt::Key_D:
            this->direction = RIGHT;
            this->walking = !this->walking;
            this->rect.translate(TRANSLATE_POINT * 2,0);
            break;
        case Qt::Key_S:
            this->direction = BOTTOM;
            this->rect.translate(0,TRANSLATE_POINT * 2);
            break;
        case Qt::Key_H:
            this->hidden = !this->hidden;
            break;
        case Qt::Key_Right: 
            if (this->weapon < ROCKET_LAUNCHER){
                this->weapon = (WEAPON) (((int)this->weapon) + 1);
            } else {
                this->weapon = PISTOL;
            }
            break;
        case Qt::Key_Left: 
            if (this->weapon > PISTOL){
                this->weapon = (WEAPON)((int)this->weapon - 1);
            } else {
                this->weapon = ROCKET_LAUNCHER;
            }
            break;
        default:
            break;
    }
    
    // Modify the path accoring to direction, hidden status, and weapon
    QString str, path;
    path = IMAGE_PATH"player/";
    switch (this->direction) {
        case TOP:
            path += "top/";
            break;
        case RIGHT:
            path += "right/";
            break;
        case BOTTOM:
            path += "bottom/";
            break;
        case LEFT:
            path += "left/";
            break;
        default:
            break;
    }
    path += (this->hidden) ? "hidden.png" : "";
    if (!this->hidden){
        switch (this->weapon) {
            case PISTOL:
                path += "pistol";
                break;
            case MACHINE_GUN:
                path += "machine";
                break; 
            case ROCKET_LAUNCHER:
                path += "rocket";
            default:
                break;
        }
        path += (this->walking) ? "1" : "0";
        path += ".png";
    }
    this->image->load(path);
    boundCheck();
}

// Make sure the player stays in bounds
void Player::boundCheck(){
    if (this->rect.top() < 0)
        this->rect.moveTo(this->rect.left(), 0);
    if (this->rect.bottom() > this->parentWidget()->height()) 
        this->rect.moveTo(this->rect.left(), this->parentWidget()->height() - this->rect.height());
    if (this->rect.left() <= 0) 
        this->rect.moveTo(0, this->rect.top());
    if (this->rect.right() >= this->parentWidget()->width()) 
        this->rect.moveTo(this->parentWidget()->width() - this->rect.width(), this->rect.top());
}