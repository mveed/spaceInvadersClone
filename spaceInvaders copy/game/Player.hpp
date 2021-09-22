//
//  Player.hpp
//  game
//
//  Created by Matthew Veeder on 9/20/21.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>

class Player{

public:
    float xPos;
    float yPos;
    sf::RectangleShape playerImage;
    Player();
    void updatePos(float pos);
    float getXPos();

};

#endif /* Player_hpp */
