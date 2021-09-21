//
//  EnemyBullet.hpp
//  game
//
//  Created by Matthew Veeder on 9/21/21.
//

#ifndef EnemyBullet_hpp
#define EnemyBullet_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class EnemyBullet{
public:
    EnemyBullet(float x, float y);
    sf::RectangleShape enemyBulletImage;
    float updateYPos();
    float getXPos();
    bool isAlive = true;

    bool randomizeEnemyBullets();
    
private:
    float xPos;
    float yPos;

};

#endif /* EnemyBullet_hpp */
