//
//  explosion.hpp
//  game
//
//  Created by Matthew Veeder on 9/21/21.
//

#ifndef explosion_hpp
#define explosion_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Explosion{

public:
    Explosion(float x, float y);
    sf::CircleShape explosionImage;
    float xPos;
    float yPos;
    bool isAlive;
    int life = 10;
    
    void update();
    float getXPos();
    float getYPos();
    bool stillAlive();
};

#endif /* explosion_hpp */
