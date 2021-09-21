//
//  EnemyBullet.cpp
//  game
//
//  Created by Matthew Veeder on 9/21/21.
//
#include "EnemyBullet.hpp"

// uses random number to decide when to create a new bullet
bool randomizeEnemyBullets(){
    int x = rand() % 10000;
    return (x > 9985);
}

// bullet moves down screen, return value
// to update setPosition
float EnemyBullet::updateYPos(){
    return yPos += 6;
}

// constructor
// enemy bullet differs from player bullet in that
// y value can change as enemies move, so have to pass in
// two parameters
EnemyBullet::EnemyBullet(float x, float y){
    sf::RectangleShape bulletSprite(sf::Vector2f(8, 12));
    bulletSprite.setFillColor(sf::Color(255, 255, 255));
    xPos = x;
    yPos = y;
    enemyBulletImage = bulletSprite;
}

// return xpos for setPosition updates
float EnemyBullet::getXPos(){
    return xPos;
}







