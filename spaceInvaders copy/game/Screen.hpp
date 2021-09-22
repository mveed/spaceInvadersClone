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
    sf::Text gameOverText;
    sf::Font gameFont;
    bool gameOver = false;
    
    float turningDistance = 0;
    float enemiesKilled = 0;
    float distance = 1;
    int shotCounter = 30;
    int gameLevel = 1;
    int loops = 0;
    
    const int windowWidth = 1200 * 1.5;
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
    
    // default while loop initial behavior
    // clear window, check that window has not been exited
    void windowCheckAndClear(sf::RenderWindow & window);
    void updateGameStatistic(sf::RenderWindow & window);
    int calculateScore();
    void updateDistance();
    void setExplosion(int idx, sf::RenderWindow & window);
    void levelUp();
    
    
    
    void gameOverReset(std::string & gameState, sf::RenderWindow & window);
    
};



#endif /* Screen_hpp */
