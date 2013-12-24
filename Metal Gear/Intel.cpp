
#include "Intel.h"
#include "GameBoard.h"

//Constructor
Intel::Intel(QWidget *parent, Coordinate pos):Object(parent){
    QString path;
    int x, y;
    this->image = new QImage;
    int level = ((GameBoard *)this->parentWidget())->getLevel();
    // Load image and adjust the size based on level
    path.sprintf(IMAGE_PATH"level%d/intel.png",level);
    this->image->load(path);
    switch (level) {
        case 1: x = 30; y = 27; break;
        case 2: x = 19; y = 45; break;
        case 3: x = 21; y = 33; break;
        default:break;
    }
    this->rect.setRect(pos.x, pos.y, x, y);
}

// Moves the intel to its current position (static)
void Intel::moveObject(){
    return;
}