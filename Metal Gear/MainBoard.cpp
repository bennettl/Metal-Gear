#include "MainBoard.h"

MainBoard::MainBoard(QWidget *parent):QWidget(parent){
    this->setGeometry(80,100,1100,520);
    this->setFixedSize(1100, 520);
    this->setWindowTitle("Metal Gear");
    this->mainMenu      = new MainMenu(this);
    this->instruction   = new Instruction(this);
    this->gameBoard     = new GameBoard(this);
    this->menu          = new Menu(this);
    
    this->gameBoard->setMenu(this->menu);
    this->displayMainMenu();
    
    // Set background stylsheet of mainboard
    char buffer [100];
    sprintf (buffer, "background-image: url(%s/pattern.png)",IMAGE_PATH);
    this->setStyleSheet(buffer);
    
    // Fills backgroun dcolor with gray
    //setPalette(QPalette(QColor(91, 91, 91)));
    //setAutoFillBackground(true);
}

// Display main menu and hides everything else
void MainBoard::displayMainMenu(){
    this->currentDisplay = MENU;
    this->instruction->hide();
    this->gameBoard->hide();
    this->menu->hide();
    this->gameBoard->endGame();
    this->gameBoard->restartGame();
    this->mainMenu->show();
}

// Display main instruction and hides everything else
void MainBoard::displayInstruction(){
    this->currentDisplay = INSTRUCTIONS;
    this->mainMenu->hide();
    this->mainMenu->updateList(0);
    this->gameBoard->hide();
    this->menu->hide();
    this->instruction->show();
}

// Display gameboard and hides everything else
void MainBoard::displayGameBoard(){
    this->currentDisplay = GAME;
    this->mainMenu->hide();
    this->mainMenu->updateList(0);
    this->instruction->hide();
    this->gameBoard->show();
    this->menu->show();
}

// Sends the event to the approriate display
void MainBoard::keyPressEvent(QKeyEvent *event){
    switch (this->currentDisplay) {
        case MENU: QApplication::sendEvent(this->mainMenu, event); break;
        case INSTRUCTIONS: QApplication::sendEvent(this->instruction, event); break;
        case GAME: QApplication::sendEvent(this->gameBoard, event); break;
        default:break;
    }
}