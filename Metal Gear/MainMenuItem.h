#ifndef MainMenuItem_h
#define MainMenuItem_h

#include <QtGui/qwidget.h>
#include <QtGui/qimage.h>
#include "Object.h"

enum ITEM_TYPE {START, INSTRUCTION, QUIT, NEXT, FINISH};

// Buttons to be used on main menu

class MainMenuItem : public QWidget{
    Coordinate pos;
    QImage *image;
    QRect rect;
    bool selected;
    ITEM_TYPE type;
    public:
        // Constructor
        MainMenuItem(QWidget *parent = 0, ITEM_TYPE type = START);
        // Creates path for image;
        QString createPath();
        // Getters
        QImage* getImage();
        QRect getRect();
        ITEM_TYPE getType();
        bool getSelected();
        // Setter
        void setSelected(bool selected);
        // Destructor
        ~MainMenuItem();
};

#endif