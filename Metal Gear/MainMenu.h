#ifndef MainMenu_h
#define MainMenu_h

#include <QtGui/qwidget.h>
//#include <QMouseEvent>
#include <QtGui/qevent.h>
#include <QtGui/qcursor.h>
#include "LinkedList.h"
#include "MainMenuItem.h"

// First screen user sees when application launches

class MainMenu: public QWidget{
    Linkedlist<MainMenuItem*> itemList;
    public:
        // Constructor
        MainMenu(QWidget *parent = 0);
        // Updates the selected index of the list
        void updateList(int index);
    private:
        // Creates a list of menu items
        void createMenuItems();
        // Updates the new selected item
        // Peforms the appropriate function when item is pressed
        void itemPressed(ITEM_TYPE type);
        // Removes the list of menu items
        void removeList();
        void keyPressEvent(QKeyEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void paintEvent(QPaintEvent *event);
};

#endif
