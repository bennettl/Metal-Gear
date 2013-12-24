#ifndef Menu_h
#define Menu_h

#include <QtGui/qwidget.h>
#include "Object.h"

// Right panel for containing game info

class Menu: public QWidget {
    int score, lives, level;
    WEAPON currentWeapon;
    public:
        // Constructor
        Menu(QWidget *parent = 0);
        // Update the stats of the menu
        void updateMenu(int score, int lives, int level, WEAPON weapon);
        // Draws the menu
        void paintEvent(QPaintEvent *event);
};

#endif