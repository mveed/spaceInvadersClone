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
    
    float getXPos();
    float getYPos();
    void updatePos(float x, float y);
    bool stillAlive();
    void kill();

};

#endif /* Enemy_hpp */
