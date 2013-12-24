#include "GameBoard.h"
#include "MainBoard.h"
#include "Soldier.h"
#include "Scorpion.h"
#include "Assassin.h"
#include "Missile.h"
#include "TMissile.h"
#include "Icespike.h"
#include "Snowball.h"
#include "Life.h"
#include "Bomb.h"
#include "Cactus.h"
#include "Rock.h"
#include "Bullet.h"
#include "Rocket.h"
#include "Intel.h"

#include <QtGui/qevent.h>
#include <QtGui/qpainter.h>


//Constructor
GameBoard::GameBoard(QWidget *parent):QWidget(parent){
    this->score          = 0;
    this->lives          = 10;
    this->level          = ONE;
    this->newLevel       = true;
    this->pause          = false;
    this->alive          = true;
    this->projectileFire = false;
    this->time           = 110;
    srand(std::time(0));
    
	// Set the width and height to be a percentage of the parents
	this->setGeometry(parent->width() * .015,parent->height() * .03 ,parent->width() * .727 , parent->height() * .94);   

    // Get the style sheet dynamically
    this->updateGameBackground();
    
    levelOneObjects();
    repaint();
}

// Instantiate all level three objects and store them into objectList
void GameBoard::levelOneObjects(){
    this->createPlayer(); 
    this->createMonster(SOLDIER);
    this->createMissile();
    this->createLife();
    this->createBomb();
    this->createIntel();
}

// Instantiate all level one objects and store them into objectList
void GameBoard::levelTwoObjects(){
    this->createPlayer(); 
    this->createMonster(SCORPION);
    this->createTMissile();
    this->createTMissile();
    this->createLife();
    this->createCactus();
    this->createIntel();
}

// Instantiate all level two objects and store them into objectList
void GameBoard::levelThreeObjects(){
    this->createPlayer(); 
    this->createAssassin();
    this->createAssassin();
    this->createLife();
    this->createRock();
    this->createIcespike();
    this->createIntel();
    this->createSnowball();
}

// Set menu to be gameboard's menu
void GameBoard::setMenu(Menu *menu){
    this->menu = menu;
}

// Returns the level
LEVEL GameBoard::getLevel(){
    return this->level;
}

// Depending on what key is pressed, set the appropriate values
void GameBoard::keyPressEvent(QKeyEvent *event){
    if (newLevel && event->key() == Qt::Key_Space){
        this->newLevel  = false;
        this->gameTimer = startTimer(this->time);
    } else if (event->key() == Qt::Key_P){
        pauseGame();
    } else if (!alive && event->key() == Qt::Key_R) {
        restartGame();
    } else if (event->key() == Qt::Key_Q) {
        // If user presses q, go back to main menu
        ((MainBoard *)this->parentWidget())->displayMainMenu();
    } else if (!pause && alive) {
        // If the game is not paused and user is still alive, process the keys
        this->player->keyMoveObject(event->key());
        // If user has switched weapons with left and right arrow keys, update the menu 
        if ((event->key() == Qt::Key_Right || event->key() == Qt::Key_Left)){
            this->menu->updateMenu(this->score, this->lives, this->level, this->player->getWeapon());
        }
        // If player has colided with another object, perform the result
        if (this->player->isCollided(this->index,this->objectList)){
            playerCollision();
        }
        // If the space key is pressed and user hasn't shot a projectile within the timer, create the projectile
        if (event->key() == Qt::Key_Space && !this->projectileFire){
            createProjectile(this->player->getWeapon());
        }
    } 
}

// Everytime repaint() is called, perform the appropriate action
void GameBoard::paintEvent(QPaintEvent *event){
    QPainter painter(this);

    // Draw all objects
    for (int i = 0; i < objectList.size(); i++) {
        Object *obj = objectList.at(i);
        painter.drawImage(obj->getRect(), *obj->getImage());
    }

    // Depending if it is a new level, paused, or user is out lives paint a menu
    if (this->newLevel || this->pause || !this->alive){
        QImage image;
        QString str;
        
        // Depending on what the status is, display the appropriate menu
        if (this->newLevel){
            str.sprintf("level%d/logo.png",this->level);
        } else if (this->pause){
            str = "gamepause.png";
        } else if (!this->alive){
            str = "gameover.png";
        }
        image.load(IMAGE_PATH + str);
        painter.translate(QPoint((this->width() - image.width())/2, (this->height() - image.height())/2));
        painter.drawImage(0, 0, image);
    }
    painter.resetTransform();
}

// Every time the timer is reached, perform the appropriate action
void GameBoard::timerEvent(QTimerEvent *event){
    if (event->timerId() == this->gameTimer){
        if (alive && this->lives <= 0){
            endGame();
        } else if (!pause && alive){
            moveAll();
            repaint();
        }
    } else if (event->timerId() == this->assassinTimer){
        // Time to create an assassin
        this->createAssassin();
        killTimer(this->assassinTimer);
    } else if (event->timerId() == this->projectileTimer){
        // Timeout finished for projectile
        this->projectileFire = false;
        killTimer(this->projectileTimer);
    }
}

// Depending if the game is paused or not, perform the appropriate action
void GameBoard::pauseGame(){
    if (this->pause) {
        this->pause = false;
        this->gameTimer = startTimer(this->time);
    } else {
        this->pause = true;
        killTimer(this->gameTimer);
        repaint();
    }
}

// Sets alive to false, kill the timer, and repaint
void GameBoard::endGame(){
    this->alive = false;
    killTimer(gameTimer);
    repaint();
}

// Set alive to true and reset lives, objects, and game state
void GameBoard::restartGame(){
    this->lives     = 10;
    this->score     = 0;
    this->alive     = true;
    this->newLevel  = true;
    this->level     = ONE;
    
    // Upate the game background iamge with the current level
    this->updateGameBackground();

    objectList.clearList();
    levelOneObjects();
    this->menu->updateMenu(this->score,this->lives,this->level, this->player->getWeapon());
    repaint();
}

// Create player
void GameBoard::createPlayer(){
    Coordinate pos;   
    pos.x        = this->width()/2;
    pos.y        = this->height()/2 - 50;
    this->player = new Player(this,pos);
    objectList.push_back(player);
}

// Create assassin
void GameBoard::createAssassin(){
    Coordinate pos      = {0,0};
    Assassin *assassin  = new Assassin(this,pos);
    bool intersect      = false;
    int posx[2]         = {0, this->width() + 10};
    int posy[2]         = {50, this->height() - 50};    
    // Keep changing the position until it doesn't intersect any objects
    do {
        intersect   = false;
        int random  = (int) ((double)rand()/(double)RAND_MAX + 0.5);
        pos.x       = posx[random];
        pos.y       = posy[random];
        assassin->setPosition(pos.x, pos.y);
        // If assassin with another assassins, set the boolean to true
        for (int i = 0; i < objectList.size(); i++) {
            Object *obj = objectList.at(i);
            if (dynamic_cast<Assassin *>(obj)) {
                if (assassin->getRect().intersects(obj->getRect())){ 
                    intersect = true;
                }
            }
        }
        if (!intersect) break;
    } while (true);
    objectList.push_back(assassin);
}

// Create a projectile, depending on weapon
void GameBoard::createProjectile(WEAPON type){
    Coordinate pos;
    DIRECTION dir = this->player->getDirection();    
    pos.x = this->player->getRect().x();
    pos.x = (dir == LEFT) ? pos.x - 2 : pos.x + this->player->getRect().width() ;
    pos.y = this->player->getRect().y() + 12;
    
    if (type == PISTOL || type == MACHINE_GUN){
        Bullet *bullet = new Bullet(this,pos,dir);
        objectList.push_back(bullet);
        
        if (type == MACHINE_GUN){
            // Depending on direction change position of bullet
            switch (dir) {
                case TOP: pos.y -= 32; break;
                case RIGHT: pos.x += 32; break;
                case LEFT: pos.x -= 32; break;
                case BOTTOM: pos. y += 32; break;
                default: break;
            }
            bullet = new Bullet(this,pos,dir);
            objectList.push_back(bullet);
            // Depending on direction change position of bullet
            switch (dir) {
                case TOP: pos.y -= 32; break;
                case RIGHT: pos.x += 32; break;
                case LEFT: pos.x -= 32; break;
                case BOTTOM: pos. y += 32; break;
                default: break;
            }
            bullet = new Bullet(this,pos,dir);
            objectList.push_back(bullet);
        }
    } else {
        Rocket *rocket = new Rocket(this,pos,dir);
        objectList.push_back(rocket);
    }
    // Prevents projectiles from being shot continously
    this->projectileFire  = true;
    this->projectileTimer = startTimer(700);
}

// Create all soldiers
void GameBoard::createMonster(MONSTER type){
    Coordinate pos;
    bool place = false;
    Monster *monster = NULL;
    
    // Monsters spawn from the left
    for (int i = (type == SOLDIER) ? 80 : 130; i < this->height(); i += 170){
        pos.y = i;
        // Switch up positions of the soldiers in the x coordinate
        if (place){
            pos.x  =  0;
            place  = false;
        } else{
            pos.x  = 30;
            place  = true;
        }
        // Depending on what type of monster it is, create it
        if (type == SOLDIER){
            monster = new Soldier(this,pos);
        } else {
            // Only create two scropions
            if (i > 300) break;
            monster = new Scorpion(this,pos);
        }
        objectList.push_back(monster);
    }
    
    // Monsters spawn from the right
    for (int i = (type == SOLDIER) ? 170: 160; i < this->height(); i += 160){
        pos.y = i;
        // Switch up positions of the soldiers in the x coordinate
        if (place){
            pos.x  = this->width() - 20;
            place  = false;
        } else{
            pos.x  = this->width() - 50;
            place  = true;
        }
        // Depending on what type of monster it is, create it
        if (type == SOLDIER){
            monster = new Soldier(this,pos);
        } else {
            // Only create two scropions
            if (i > 330) break;
            monster = new Scorpion(this,pos);
        }
        objectList.push_back(monster);
    }  
}

// Create all Missile
void GameBoard::createMissile(){
    Coordinate pos;
    bool place = false;
    
    // Missles spawn from the bottom
    for (int i = this->width() + 50; i > 0; i -= 150){
        pos.x = i;
        // Switch up positions of the missiles in the columns
        if (place){
            pos.y   = this->height() - 20;
            place   = false;
        } else{
            pos.y   = this->height() - 50;
            place   = true;
        }
        Missile *missile = new Missile(this,pos);
        objectList.push_back(missile);
    }
}

// Create a tracking missile
void GameBoard::createTMissile(){
    Coordinate finalPos;
    finalPos.x = this->player->getRect().x();
    finalPos.y = this->player->getRect().y();
    TMissile *tmissile = new TMissile(this,finalPos);
    objectList.push_back(tmissile);
}

// Create an ice spike
void GameBoard::createIcespike(){
    Coordinate startPos;
    startPos.x = this->player->getRect().x();
    startPos.y = -60;
    Icespike *icespike = new Icespike(this,startPos);
    objectList.push_back(icespike);
}


// Create all life items
void GameBoard::createLife(){   
    Coordinate pos;
    // For every 300px on x, plce a bomb
    for (int i = 100; i < this->width(); i += 300) {
        // For every 300px on y, plce a bomb
        for (int j = 70; j < this->height() - 50; j += 300) {
            pos.x    = i;
            pos.y    = j;
            Life *life = new Life(this,pos);
            objectList.push_back(life);
        }
    }
}

// Create all bombs
void GameBoard::createCactus(){
    Coordinate pos;
    // For every 5th column, place a cactus
    for (int i = 50; i < this->width(); i += 150){
        // For every 5th row, place a cactus
        for (int j = 35; j < this->height() - 50; j += 170){
            pos.x  = i;
            pos.y  = j;
            Cactus *cactus = new Cactus(this,pos);
            objectList.push_back(cactus);
        }
    }     
}


// Create all bombs
void GameBoard::createBomb(){
    Coordinate pos;
    // For every 5th column, place a bomb
    for (int i = 50; i < this->width(); i += 125){
        // For every 5th row, place a bomb
        for (int j = 35; j < this->height() - 50; j += 125){
            pos.x  = i;
            pos.y  = j;
            Bomb *bomb = new Bomb(this,pos);
            objectList.push_back(bomb);
        }
    }     
}

// Create all bombs
void GameBoard::createRock(){
    Coordinate pos;
    // For every 5th column, place a rock
    for (int i = 50; i < this->width(); i += 125){
        // For every 5th row, place a rock
        for (int j = 35; j < this->height() - 50; j += 125){
            pos.x  = i;
            pos.y  = j;
            Rock *rock = new Rock(this,pos);
            objectList.push_back(rock);
        }
    }     
}

// Create a Intel
void GameBoard::createIntel(){
    Coordinate pos;
    bool intersect  = false;
    Intel *intel      = new Intel(this,pos);

    // Keep changing the position until it doesn't intersect any objects
    do {
        intersect   = false;
        pos.x       = rand() % (this->width() - 50);
        pos.y       = rand() % (this->height() - 50);
        intel->setPosition(pos.x, pos.y);
        // If rects intersets, set the boolean to true
        for (int i = 0; i < objectList.size(); i++) {
            if (intel->getRect().intersects(objectList.at(i)->getRect())){                       
                intersect = true;
            }
        }
        if (!intersect) break;
    } while (true);
    objectList.push_back(intel);     
}

// Create all snowball
void GameBoard::createSnowball(){
    Coordinate pos;    
    // Snowball spawn from the top
    for (int i = this->width() + 50; i > 0; i -= 50){
        pos.x = i;
        pos.y = -(rand() % 600);
        Snowball *snowball = new Snowball(this,pos);
        objectList.push_back(snowball);
    }
}

// Loop through and move every object
void GameBoard::moveAll() {
    for (int i = 0; i < objectList.size(); i++) {
        Object *obj = objectList.at(i);
        
        // If object is an assassin, send a different move method
        if (dynamic_cast<Assassin *>(obj)){
            ((Assassin*)obj)->moveObject(objectList, this->player);
        } else{  
            obj->moveObject();
        }
        
        // If tracking missile is out of bounds, then remove the object and start a new one
        if (dynamic_cast<TMissile *>(obj) && ((TMissile *)obj)->boundCheck()){
            removeObj(i);
            this->createTMissile();
            continue;

        }
        
        // If tracking missile is out of bounds, then remove the object and start a new one
        if (dynamic_cast<Icespike *>(obj) && ((Icespike *)obj)->boundCheck()){
             removeObj(i);
             this->createIcespike();
             continue;
        }
        
        // Check if the objects intersect with the player
        if (!dynamic_cast<Player *>(obj) && !obj->getTouchedOnce() && obj->getRect().intersects(this->player->getRect())){
            this->index = i;
            playerCollision();
            continue;
        } 
        
        // Check projectile
        if (dynamic_cast<Projectile *>(obj)){            
            // Check if projectile is out of bounds and delete it if it is
            QRect projRect = obj->getRect();
            
            if (projRect.x() > this->width() || projRect.x() < 0){
                removeObj(i);
            } else {
                // Compare each object to the projectile
                for (int j = 0; j < objectList.size(); j++) {
                    Object *obj2 = objectList.at(j);
                    // Check if projectile collided with monster bullet
                    if (dynamic_cast<Monster*>(obj2) && !obj2->getTouchedOnce() && projRect.intersects(obj2->getRect())){
                        // If its an assasin, then start the timer to create a new one
                        if (dynamic_cast<Assassin *>(obj2)){
                            this->assassinTimer = startTimer(2000);
                        }
                        removeObj(i);
                        this->index = j;
                        monsterCollision();
                    }
                }
            }
        }
    }
}

// Depending on the collion, perform the appropriate result
void GameBoard::playerCollision(){
    Object *obj = objectList.at(this->index);

    if ((dynamic_cast<Monster *>(obj)|| dynamic_cast<Missile*>(obj) || dynamic_cast<Cactus *>(obj) || dynamic_cast<Rock *>(obj)) && !obj->getTouchedOnce() && !this->player->getHidden()){ 
        // If object is a monster missle, this is the first touch, and player is not hidden
        this->lives--;
        obj->setTouchedOnce(true);
    } else if (dynamic_cast<Life *>(obj)){ // Object is life item
        // Only increment the life count if lives less than 10
        if (this->lives < 10){
            this->lives++;
            removeObj(this->index);
        }
    } else if (dynamic_cast<Bomb *>(obj)){ // Object is bomb
        this->lives--;
        // Change player image depending on direction
        if (this->player->getDirection() == RIGHT)
            this->player->getImage()->load(IMAGE_PATH"playerRightHit.png");
        else 
            this->player->getImage()->load(IMAGE_PATH"playerLeftHit.png");
        removeObj(this->index);
    } else if (dynamic_cast<Intel *>(obj)){ // Object is Intel
        removeObj(this->index);
        createIntel();
        addScore();
    }
    
    // Update the menu's stats
    this->menu->updateMenu(this->score, this->lives, this->level, this->player->getWeapon());
}

// When a bullet collided with a monster, add score and update the menu
void GameBoard::monsterCollision(){    
    removeObj(this->index);
    addScore();
    this->menu->updateMenu(this->score, this->lives, this->level, this->player->getWeapon());
}

// Removes object from objectList based on coordinates
void GameBoard::removeObj(int index){
    delete objectList.at(index);
    objectList.eraseObj(objectList.begin() + index);
}

// Increments the score and update the level if score is high enough
void GameBoard::addScore(){
    this->score += 10;
    // For every 50 points user score, increment the time and level
    if (!(this->score % 50) && this->level < THREE){
        this->time /= 1.1;
        updateLevel();
    }
}

// Increment the level and set new level to true
void GameBoard::updateLevel(){
    this->level = (LEVEL)(((int)this->level) + 1);
    this->newLevel = true;
    
    // Update game background
    this->updateGameBackground();

    // Clear the objectlist and put in new objects
    objectList.clearList();
    if (this->level == TWO){
        levelTwoObjects();
    } else if (this->level == THREE) {
        levelThreeObjects();
    }
    killTimer(this->gameTimer);
    repaint();
}

// Updates the background stylesheet of gameboard base on level
void GameBoard::updateGameBackground(){
    char buffer [200];
    sprintf (buffer, "background-image: url(%slevel%d/pattern.png)",IMAGE_PATH, this->level);
    this->setStyleSheet(buffer);
}