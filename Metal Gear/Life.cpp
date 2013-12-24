
#include "Life.h"
#include "GameBoard.h"

//Constructor
Life::Life(QWidget *parent, Coordinate pos):Object(parent){
    this->image = new QImage;
    LEVEL level = ((GameBoard *)this->parentWidget())->getLevel();
    QString path;
    path.sprintf(IMAGE_PATH"level%d/life.png",level);
    this->image->load(path);
    this->rect.setRect(pos.x, pos.y, 20, 20);
}

// Moves the life item to its current position (static)
void Life::moveObject(){
    return;
}

