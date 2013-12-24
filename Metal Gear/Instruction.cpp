
#include "Instruction.h"
#include <QtGui/qwidget.h>
#include <QtGui/qevent.h>
#include <QtGui/qpainter.h>
#include "MainBoard.h"
#include "Object.h"

Instruction::Instruction(QWidget *parent):QWidget(parent){
    // Set the width and height to be a percentage of the parents
	this->setGeometry(0,0 ,parent->width(), parent->height());
    QString str = "background-image: url(";
    str.append(IMAGE_PATH);
    str.append("pattern.png)");
    this->setMouseTracking(true);
    this->setStyleSheet(str);
    this->setMouseTracking(true);
    this->pagenum = PAGE_ONE;
    this->next    = new MainMenuItem(this,NEXT);
    this->finish  = new MainMenuItem(this,FINISH);
}

// Changes the page
void Instruction::changePage(){
    // Depending on the page, perform the approprate action
    if (this->pagenum == PAGE_ONE){
        this->pagenum = PAGE_TWO;
    } else {
        this->pagenum = PAGE_ONE;
        ((MainBoard *)this->parentWidget())->displayMainMenu();
    }
}

void Instruction::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QImage image;
    // Depending on the page, draw the appropriate image and button
    if (this->pagenum == PAGE_ONE){
        image.load(IMAGE_PATH"instruction/page1.png");
        painter.drawImage(102, 61, image);
        painter.drawImage(this->next->getRect(),*this->next->getImage());
    } else {
        image.load(IMAGE_PATH"instruction/page2.png");
        painter.drawImage(88, 61, image);
        painter.drawImage(this->finish->getRect(),*this->finish->getImage());
    }
}

void Instruction::keyPressEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Right){
        this->changePage();
    }
}

void Instruction::mouseMoveEvent(QMouseEvent *event){
    int hover = false;
    this->next->setSelected(false);
    this->finish->setSelected(false);

    // If the mouse is hovering over a menu item, mark that item as selected
    if (this->pagenum == PAGE_ONE && next->getRect().contains(QPoint(event->x(), event->y()))){
        this->next->setSelected(true);
        hover = true;
    } else  if (this->pagenum == PAGE_TWO && finish->getRect().contains(QPoint(event->x(), event->y()))){
        this->finish->setSelected(true);
        hover = true;
    }
    QCursor cursor = (hover) ? Qt::PointingHandCursor : Qt::ArrowCursor;
    QWidget::setCursor(cursor);
    repaint();
}

void Instruction::mouseReleaseEvent(QMouseEvent *event){
    // If the mouse is hovering over the next or finish menu item, change the page
    if ((this->pagenum == PAGE_ONE && next->getRect().contains(QPoint(event->x(), event->y()))) || 
        (this->pagenum == PAGE_TWO && finish->getRect().contains(QPoint(event->x(), event->y())))){
        this->changePage();
    }
}











