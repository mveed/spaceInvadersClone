//
//  Screen.cpp
//  game
//
//  Created by Xiaojun Wu on 9/21/21.
//

#include "Screen.hpp"


Screen::Screen() { // populate player, enemies
    populateEnemies(20);
}

void Screen::populateEnemies( int numEnemy ) {
    float xSpace = 150;
    float ySpace = 75;
    float xStart = 150;
    float yStart = 150;
    enemies = {};
    for (int row = 0; row <= 4; row++){
        for (int col = 0; col <= 5; col++){
            Enemy newEnemy(xStart, yStart);
            // need to set the Rect bounding box to start position as well
            newEnemy.enemyBox.setPosition(xStart, yStart);
            xStart += xSpace;
            enemies.push_back(newEnemy);
        }
        xStart = 150;
        yStart += ySpace;
    }
}
