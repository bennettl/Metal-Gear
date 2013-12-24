
#include "Assassin.h"
#include "Bomb.h"

//Constructor
Assassin::Assassin(QWidget *parent, Coordinate pos):Monster(parent){
    this->image             = new QImage;
    this->direction         = RIGHT;
    this->touchedOnce       = false;
    this->image->load(IMAGE_PATH"level3/monsterRight.png");
    this->rect.setRect(pos.x, pos.y, 55, 54);
    this->bombhit           = false;
}

// Move towards player
void Assassin::moveObject(Linkedlist<Object *> &objectList, Player *player){
    int x           = player->getRect().x() - this->rect.x();
    int y           = player->getRect().y() - this->rect.y();
    int speed       = TRANSLATE_POINT * 1.5;
    this->direction = (x > 0) ? RIGHT : LEFT; 
    updateImage();
    // Move horizontal, then vertical
    if (y != 0){
        // If there is only a 10 points between assassin and player, then close the gap, else move at constant speed
        if ((y > 0 && y < 10) || (y < 0 && y > -10)){
            this->rect.translate(0 ,y);
        } else {
            this->rect.translate(0, (y > 0) ? speed : -speed);
        }
    }  else  if (x != 0) {
        // If there is only a 10 points between assassin and player, then close the gap, else move at constant speed
        if ((x > 0 && x < 10) || (x < 0 && x > -10)) {
            this->rect.translate(x, 0);
        } else {
            this->rect.translate((x > 0) ? speed : -speed, 0);
        }
    }
}

void Assassin::moveObject(){
    return;
}

void Assassin::updateImage(){
    QString str = IMAGE_PATH"level3/";
    str += (this->direction == RIGHT) ? "monsterRight.png" : "monsterLeft.png" ;
    this->image->load(str);
}




