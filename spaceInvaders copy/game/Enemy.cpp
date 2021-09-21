//
//  Enemy.cpp
//  game
//
//  Created by Matthew Veeder on 9/20/21.
//

#include "Enemy.hpp"


Enemy::Enemy(float x, float y){
    sf::CircleShape enemyShape(25);
    enemyShape.setFillColor(sf::Color(150, 150, 150));
    // create a bounding box for collision detection
    sf::RectangleShape enemyBoundingBox(sf::Vector2f(50, 50));
    enemyBox = enemyBoundingBox;
    xPos = x;
    yPos = y;
    enemyImage = enemyShape;
    isAlive = true;
}

float Enemy::getXPos(){
    return xPos;
}

float Enemy::getYPos(){
    return yPos;
}

float Enemy::updateXPos(float distance){
    xPos += distance;
    enemyBox.setPosition(xPos, yPos);
    return xPos;
}

float Enemy::updateYPos(float distance){
    yPos += distance;
    enemyBox.setPosition(xPos, yPos);
    return yPos;
}

bool Enemy::stillAlive() {
    
    return true;
}

void Enemy::kill(){
    
}


