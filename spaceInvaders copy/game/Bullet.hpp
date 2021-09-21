//
//  Bullet.hpp
//  game
//
//  Created by Matthew Veeder on 9/20/21.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Bullet{
public:
    Bullet(float x);
    sf::RectangleShape bulletImage;
    float updateYPos();
    float getXPos();
    bool isAlive = true;
    
private:
    float xPos;
    float yPos;

};

#endif /* Bullet_hpp */
