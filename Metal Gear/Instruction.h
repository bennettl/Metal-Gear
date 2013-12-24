#ifndef Instruction_h
#define Instruction_h

#include <QtGui/qwidget.h>
#include "MainMenuItem.h"

enum PAGE {PAGE_ONE, PAGE_TWO};

// Instructions page

class Instruction : public QWidget{
    PAGE pagenum;
    MainMenuItem *next, *finish;
    // Changes the page number
    void changePage();
    public:
        // Constructor
        Instruction(QWidget *parent = 0);
        void paintEvent(QPaintEvent *event);
        void keyPressEvent(QKeyEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
};

#endif