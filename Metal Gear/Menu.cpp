#include "Menu.h"
#include <QtCore/qdebug.h>
#include <QtGui/qpainter.h>
#include "Object.h"

Menu::Menu(QWidget *parent):QWidget(parent){
    QFont font("Arial", 15);
    this->setFont(font);
    this->updateMenu(0, 10, 1, PISTOL);
    // Set the width and height to be a percentage of the parents
	this->setGeometry(parent->width() * .75,parent->height() * .03 ,parent->width() * .236 , 490);
}

void Menu::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QString str;
    QImage image;
    // Draw health
    image.load(IMAGE_PATH + str.sprintf("menu/health/%d.png", this->lives));
    painter.drawImage(49,15, image);
    // Draw score
    image.load(IMAGE_PATH"menu/score.png");
    painter.drawImage(33, 60, image);
    str.sprintf("%d",this->score);
    painter.setPen(QColor(Qt::white));
    painter.drawText(QPoint(160,73),str);  
    painter.setPen(QColor(183, 183, 183));
    // Draw weapon
    image.load(IMAGE_PATH + str.sprintf("menu/weapon/%d.png", this->currentWeapon));
    painter.drawImage(105, 80, image);        
    // Draw key
    painter.drawLine(32, 140, 232, 140);  
    image.load(IMAGE_PATH + str.sprintf("level%d/key.png", this->level));
    painter.drawImage(30, 150, image);
    painter.drawLine(32, 320, 232, 320); 
    // Draw command
    image.load(IMAGE_PATH"menu/command.png");
    painter.drawImage(20, 330, image);
}

// Updates the states and repaints the menu
void Menu::updateMenu(int score, int lives, int level, WEAPON weapon){
    this->score         = score;
    this->lives         = lives;
    this->level         = level;
    this->currentWeapon = weapon;
    repaint();
}