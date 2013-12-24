
#ifndef GameBoard_h
#define GameBoard_h


#include <cstdlib>
#include <ctime>
#include "LinkedList.h"
#include "Player.h"
#include "Menu.h"

enum LEVEL {ONE = 1,TWO,THREE};
enum MONSTER {SOLDIER, SCORPION};

// Panel where user plays the game

class GameBoard: public QWidget{
    private:
        Linkedlist<Object*> objectList;
        int score, lives, speed, index;
        int time, gameTimer, assassinTimer, projectileTimer;
        bool pause, alive, newLevel, projectileFire;
        LEVEL level;
        Player *player;
        Menu *menu;
        
        // Instantiate all level one objects and store them into objectList
        void levelOneObjects();
        // Instantiate all level one objects and store them into objectList
        void levelTwoObjects();
        // Instantiate all level one objects and store them into objectList
        void levelThreeObjects();
        // Everytime repaint() is called, perform the appropriate action
        void paintEvent(QPaintEvent *event);
        // Every time the timer is reached, perform the appropriate action
        void timerEvent(QTimerEvent *event);
        // Depending on what key is pressed, set the appropriate values
        void keyPressEvent(QKeyEvent *event);
        // Depending if the game is paused or not, perform the appropriate action
        void pauseGame();
        // Creates player
        void createPlayer();
        // Creates assassin
        void createAssassin();
        // Creates the projectile based on weapon
        void createProjectile(WEAPON type);
        // Creates all monsters, depending on type
        void createMonster(MONSTER type);
        // Creates all missles
        void createMissile();
        // Creates tracking missile
        void createTMissile();
        // Creates gernade
        void createIcespike();
        // Creates all life items
        void createLife();  
        // Create all cactus
        void createCactus();
        // Create all rocks
        void createRock();
        // Creates all bombs
        void createBomb();    
        // Create a intel
        void createIntel(); 
        // Creates all snow
        void createSnowball();
        // Loop through and move every object
        void moveAll();
        // Depending on the collion, perform the appropriate result
        void playerCollision();
        // Removes object from objectList base on index
        void removeObj(int index);   
        // Depending on the collion, perform the appropriate result    
        void monsterCollision();
        // Update the score and the level if score is high enough
        void addScore();
        //Update the level
        void updateLevel();
        // Updates the background stylesheet of gameboard base on level
        void updateGameBackground();

    public:
        //Constructor
        GameBoard(QWidget *parent = 0);
        // Sets the pointer to the menu object
        void setMenu(Menu *menu);
        // Returns the level
        LEVEL getLevel();
        // Sets alive to false, kill the timer, and repaint
        void endGame();
        // Set alive to true and reset lives, objects, and start timer
        void restartGame();
};

#endif




















