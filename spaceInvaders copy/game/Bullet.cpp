//
//  Bullet.cpp
//  game
//
//  Created by Matthew Veeder on 9/20/21.
//

#include "Bullet.hpp"


float Bullet::updateYPos(){
    return yPos -= 6;
}

Bullet::Bullet(float x){
    sf::RectangleShape bulletSprite(sf::Vector2f(8, 12));
    bulletSprite.setFillColor(sf::Color(150, 150, 150));
    xPos = x;
    yPos = 1050;
    bulletImage = bulletSprite;
}

float Bullet::getXPos(){
    return xPos;
}
