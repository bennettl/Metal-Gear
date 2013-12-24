
#include "Icespike.h"

//Constructor
Icespike::Icespike(QWidget *parent, Coordinate startPos):Object(parent){
    this->image             = new QImage();
    this->image->load(IMAGE_PATH"level3/icespike.png");
    this->rect.setRect(startPos.x, startPos.y, 23, 52);
}

void Icespike::moveObject(){
    // Move horizontal and  vertical
    boundCheck();
    this->rect.translate(0,TRANSLATE_POINT * 1.5);
}

// If its out of bounds, then return true
bool Icespike::boundCheck(){
    return (this->rect.bottom() > this->parentWidget()->height()) ? true : false;    
}

