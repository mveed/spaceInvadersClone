//
//  Screen.hpp
//  game
//
//  Created by Xiaojun Wu on 9/21/21.
//

#ifndef Screen_hpp
#define Screen_hpp

#include <stdio.h>
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
    Player player;
    sf::Text scoreText;
    sf::Text levelText;
    
    Screen();  // populate player, enemies
    void populateEnemies( int numEnemies );
    
};

#endif /* Screen_hpp */
