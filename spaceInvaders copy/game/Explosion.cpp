//
//  explosion.cpp
//  game
//
//  Created by Matthew Veeder on 9/21/21.
//

#include "explosion.hpp"

Explosion::Explosion(float x, float y){
    sf::CircleShape explosionShape(rand() % 5 + 20);
    explosionShape.setFillColor(sf::Color(255, 0, 0));
    int randX = rand() % 5 - 2.5;
    int randY = rand() % 5 - 2.5;
    xPos = x + randX;  // % helps to randomize slightly where explosion is created around enemy
    yPos = y + randY;
    explosionImage = explosionShape;
    isAlive = true;
    int life = 600 ;
}

float Explosion::getXPos(){
    return xPos;
}

float Explosion::getYPos(){
    return yPos;
}

void Explosion::update(){
    life = life - 1;
    
    // if has been drawing red for 5 frames, switch to white
    if (life < 5){
        explosionImage.setFillColor(sf::Color(255, 255, 255));
    }
    
    if (life < 0){
        isAlive = false;
    }
    
}
