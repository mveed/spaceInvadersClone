//
//  Player.cpp
//  game
//
//  Created by Matthew Veeder on 9/20/21.
//

#include "Player.hpp"
#include <SFML/Graphics.hpp>


Player::Player(int x, int y){
    sf::RectangleShape playerSprite(sf::Vector2f(65, 50));
    playerSprite.setFillColor(sf::Color(150, 150, 150));
    xPos = x/2 - 100;
    yPos = y - 100;
    playerImage = playerSprite;
    playerSprite.setPosition(xPos, yPos);
}

void Player::updatePos(float pos){
    xPos = pos;
}

float Player::getXPos(){
    return xPos;
}
