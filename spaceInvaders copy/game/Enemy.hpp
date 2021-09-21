//
//  Enemy.hpp
//  game
//
//  Created by Matthew Veeder on 9/20/21.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Enemy{

public:
    Enemy(float x, float y);
    sf::CircleShape enemyImage;
    // bounding box for collision detection
    sf::RectangleShape enemyBox;
    float xPos;
    float yPos;
    bool isAlive;
    float movingDistance = 3;
    
    float getXPos();
    float getYPos();
    float updateXPos(float distance);
    float updateYPos(float distance);
    bool stillAlive();
    void kill();


};

#endif /* Enemy_hpp */
