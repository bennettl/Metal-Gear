//
//  main.cpp
//  Metal Gear
//
//  Created by Bennett Lee on 12/24/13.
//  Copyright (c) 2013 Bennett Lee. All rights reserved.
//

#include "MainBoard.h"


int main(int argc, char * argv[]){
    QApplication app(argc,argv);
    MainBoard newgame;
    newgame.show();
    return app.exec();
}