//
//  Player.cpp
//  game
//
//  Created by Matthew Veeder on 9/20/21.
//

#include "Player.hpp"
#include <SFML/Graphics.hpp>


Player::Player(){
    sf::RectangleShape playerSprite(sf::Vector2f(65, 50));
    playerSprite.setFillColor(sf::Color(150, 150, 150));
    xPos = 1200*1.5/2;
    yPos = 1100;
    playerImage = playerSprite;
    playerImage.setPosition(xPos, yPos);
}

void Player::updatePos(float pos){
    xPos = pos;
}

float Player::getXPos(){
    return xPos;
}
