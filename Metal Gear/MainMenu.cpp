#include <QtGui/qpainter.h>
#include <QtGui/qapplication.h>
#include "MainMenu.h"
#include "MainBoard.h"
#include "Object.h"

MainMenu::MainMenu(QWidget *parent):QWidget(parent){
    // Set the width and height to be a percentage of the parents
	this->setGeometry(0,0 ,parent->width(), parent->height());
    QString str = "background-image: url(";
    str.append(IMAGE_PATH);
    str.append("pattern.png)");
    this->setMouseTracking(true);
    this->setStyleSheet(str);
    createMenuItems();
}

// Creates a list of menu items
void MainMenu::createMenuItems(){
    MainMenuItem *item = new MainMenuItem(this,START);
    this->itemList.push_back(item);
    item = new MainMenuItem(this,INSTRUCTION);
    this->itemList.push_back(item);
    item = new MainMenuItem(this,QUIT);
    this->itemList.push_back(item);
    itemList.at(0)->setSelected(true);
}

// Empties the list of menu items
void MainMenu::removeList(){
    this->itemList.clearList();
}

void MainMenu::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QImage image;
    // Draw Left Side
    image.load(IMAGE_PATH"mainmenu/left.png");
    painter.drawImage(53, 154, image);
    // Draw middile
    image.load(IMAGE_PATH"mainmenu/title.png");
    painter.drawImage(310, 95, image);
    for (int i = 0; i < itemList.size(); i++) {
        MainMenuItem *item = this->itemList.at(i);
        painter.drawImage(item->getRect(), *item->getImage());
    }
    // Right
    image.load(IMAGE_PATH"mainmenu/right.png"); 
    painter.drawImage(790, 165, image);
}

// Depending on which item is pressed, perform the appropraite operation
void MainMenu::itemPressed(ITEM_TYPE type){
    QWidget::setCursor(Qt::ArrowCursor);
    switch (type) {
        case START:
            ((MainBoard *)this->parentWidget())->displayGameBoard();
            break;
        case INSTRUCTION:
            ((MainBoard *)this->parentWidget())->displayInstruction();
            break;
        case QUIT:
            qApp->exit();
            break;
        default:
            break;
    }
}

// Update the selected boolean of each item
void MainMenu::updateList(int index){
    // Make sure every element is false
    for (int i = 0; i < itemList.size(); i++) {
        MainMenuItem *item = itemList.at(i);
        if (item->getSelected()){
            item->setSelected(false);
        }
    }
    // Only set the one at selected index to be true
    itemList.at(index)->setSelected(true);
    repaint();
}


// Sends the event to the gameboard
void MainMenu::keyPressEvent(QKeyEvent *event){
    int index = 0;
    
    // Find the index of selected item
    for (int i = 0; i < itemList.size(); i++) {
        MainMenuItem *item = itemList.at(i);
        if (item->getSelected()){
            index = i;
        }
    }
    // Depeding on the key pressed, peform the appropriate operation
    switch (event->key()) {
        case Qt::Key_Up:
        case Qt::Key_W:
            index--;
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            index++;
            break;
        case Qt::Key_Enter:
        case Qt::Key_Return:
            this->itemPressed(itemList.at(index)->getType());
            break;
        default:
            break;
    }
    
    if (index < 0) index = itemList.size() - 1;
    if (index >= itemList.size())  index = 0;
    this->updateList(index);
}

void MainMenu::mouseMoveEvent(QMouseEvent *event){
    int hover = false;
    for (int i = 0; i < itemList.size(); i++) {
        MainMenuItem *item = itemList.at(i);
        // If the mouse is hovering over a menu item, mark that item as selected
        if (item->getRect().contains(QPoint(event->x(), event->y()))){
            this->updateList(i);
            hover = true;
        }
    }
    QCursor cursor = (hover) ? Qt::PointingHandCursor : Qt::ArrowCursor;
    QWidget::setCursor(cursor);
}

void MainMenu::mouseReleaseEvent(QMouseEvent *event){
    for (int i = 0; i < itemList.size(); i++) {
        MainMenuItem *item = itemList.at(i);
        // If the mouse is pressed on a menu item, perform the appropraite operation
        if (item->getRect().contains(QPoint(event->x(), event->y()))){
            this->itemPressed(itemList.at(i)->getType());
        }
    }
    
}