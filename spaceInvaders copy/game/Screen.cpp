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

void Screen::deleteGameObjects(std::vector<Enemy> & a, std::vector<EnemyBullet> & b, std::vector<Bullet> & c, std::vector<Explosion> & d){
     // delete all enemies
            for (int i = 0; i < a.size(); i++){
                a.pop_back();
            }
            for (int i = 0; i < b.size(); i++){
                b.pop_back();
            }
            for (int i = 0; i < c.size(); i++){
                c.pop_back();
            }
            for (int i = 0; i < d.size(); i++){
                d.pop_back();
            }
}
