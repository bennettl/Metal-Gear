#include "MainMenuItem.h"

// Constructor
MainMenuItem::MainMenuItem(QWidget *parent, ITEM_TYPE type):QWidget(parent){
    int x, y;
    
    // Adjust position and dimention according to the item type
    switch (type) {
        case START:
            this->pos.x = 407; x = 277;
            this->pos.y = 220; y = 49;
            break;
        case INSTRUCTION:
            this->pos.x = 395; x = 291;
            this->pos.y = 290; y = 36;
            break;
        case QUIT:
            this->pos.x = 488; x = 103;
            this->pos.y = 350; y = 37;
            break;
        case NEXT:
            this->pos.x = 965; x = 77;
            this->pos.y = 440; y = 25;
            break;
        case FINISH:
            this->pos.x = 960; x = 95;
            this->pos.y = 440; y = 25;
            break;
        default:
            break;
    }
    this->selected  = false;
    this->type      = type;
    QString path    = createPath();
    this->image     = new QImage();
    this->image->load(path);
    this->rect.setRect(pos.x, pos.y, x, y);
}

// Returns the pointer to the image
QImage* MainMenuItem::getImage(){
    return this->image;
}

// Returns the qrect of the object
QRect MainMenuItem::getRect(){
    return this->rect;
}

// Returns the type of item
ITEM_TYPE MainMenuItem::getType(){
    return this->type;
}

// Returns the selected boolean
bool MainMenuItem::getSelected(){
    return this->selected;
}

// Returns the selected boolean
void MainMenuItem::setSelected(bool selected){
    this->selected = selected;
    QString path = createPath();
    this->image->load(path);
}

// Creates path for image;
QString MainMenuItem::createPath(){
    QString path = IMAGE_PATH"mainmenu/";
    switch (this->type) {
        case START: path += "startgame"; break;
        case INSTRUCTION: path += "instruction"; break;
        case NEXT: path += "next"; break;
        case FINISH: path += "finish"; break;
        case QUIT: path += "quit"; break;
        default: break;
    }
    path        += (this->selected) ? "1" : "0";
    path        += ".png";
    return path;
}

// Destructor
MainMenuItem::~MainMenuItem(){
    delete this->image;
}