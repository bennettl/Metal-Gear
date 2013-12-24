
#ifndef Object_h
#define Object_h

#include <QtGui/qimage.h>
#include <QtGui/qwidget.h>
#include <QtCore/qdebug.h>

// Can't have image directory in  the same directory
#define IMAGE_PATH "/Users/bennettlee/Desktop/Projects/Past/Metal Gear/images/"

typedef struct{
    int x;
    int y;
} Coordinate;

typedef struct{
    int width;
    int height;
} Size;

enum WEAPON {PISTOL, MACHINE_GUN, ROCKET_LAUNCHER};
enum DIRECTION {TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, TOP, RIGHT, LEFT, BOTTOM};

const int TRANSLATE_POINT          = 5;
const Coordinate defaultCoordinate = {0,0};
const Size defaultSize             = {0,0};

class Object: public QWidget {
    protected:
        QImage *image;
        QRect  rect;
        DIRECTION direction;
        bool touchedOnce;
    
    public:
        // Constructor
        Object(QWidget *parent = 0):QWidget(parent){};
        // Getters
        QImage* getImage();
        QRect getRect();
        bool getTouchedOnce();
        // Setters
        void setPosition(int x, int y);
        void setTouchedOnce(bool value);
        // Moves the object
        virtual void moveObject() = 0;
        // Destructor
        ~Object();
};


#endif
