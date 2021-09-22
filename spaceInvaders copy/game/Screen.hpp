//
//  Screen.hpp
//  game
//
//  Created by Xiaojun Wu on 9/21/21.
//

#ifndef Screen_hpp
#define Screen_hpp

#include <stdio.h>
#include <iostream>
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "EnemyBullet.hpp"
#include "Player.hpp"
#include "Explosion.hpp"

class Screen {
public:
    std::vector<Enemy> enemies;            
    std::vector<Bullet> playerBullets;
    std::vector<EnemyBullet> enemyBullets;
    std::vector<Explosion> explosions;
    Player player;
    sf::Text scoreText;
    sf::Text levelText;
    
    float turningDistance = 0;
    float enemiesKilled = 0;
    float distance = 2;
    int shotCounter = 0;
    
    const int windowWidth = 1200;
    const int windowHeight = 1200;
    const int moveSpeed = 10;
    
    Screen();  // populate player, enemies
    void populateEnemies( int numEnemies );
    void deleteGameObjects();
    void updateEnemies(sf::RenderWindow & window);
    void updateBullets(sf::RenderWindow & window);
    void updateEnemyBullets(sf::RenderWindow & window);
    void updateExplosion(sf::RenderWindow & window);
    bool randomizeEnemyBullets();
    void keyBoardPressed(sf::RenderWindow & window);
    
    
    
};



#endif /* Screen_hpp */
