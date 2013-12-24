#ifndef MainBoard_h
#define MainBoard_h

#include <QtGui/qapplication.h>
#include <QtGui/qwidget.h>
#include "MainMenu.h"
#include "GameBoard.h"
#include "Menu.h"
#include "Instruction.h"

enum CURRENT_DISPLAY {MENU, INSTRUCTIONS, GAME};

// Panel containing both the mainmenu and game and menu
class MainBoard: public QWidget{ 
        MainMenu *mainMenu;
        Instruction *instruction;
        GameBoard *gameBoard;
        Menu *menu;
        CURRENT_DISPLAY currentDisplay;
    public:
        // Constructor
        MainBoard(QWidget *parent = 0);
        // Shows the appropriate display
        void displayMainMenu();
        void displayInstruction();
        void displayGameBoard();
        void keyPressEvent(QKeyEvent *event);
};

#endif