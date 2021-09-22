#include <SFML/Graphics.hpp>

#include <math.h>
#include <iostream>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "EnemyBullet.hpp"
#include "Explosion.hpp"
#include "Screen.hpp"
#include <vector>
#include <string>

std::string gameState = "title";
// different state ideas -
// title
// inGame
// createNewLevel
// loseLife
// gameOver


void generateText(sf::Text & text, sf::Font & font, std::string str) {
    
    text.setString(str); // set the character size
    
}

float playerX = 600;

int main()
{



    
    

    
    // start with shot counter ready to allow player to shoot
    // when bullet fires, set to positive value
    // constantly --, then when value is <0 allow another
    // bullet to be fire
  // Create the main program window.


//  float angle = 0.0;
    
    // initiate screen elements.
    Screen screen;

    
    
    sf::RenderWindow window(sf::VideoMode(screen.windowWidth, screen.windowHeight), "My window");
      window.setFramerateLimit(60);
    

  // Run the program as long as the main window is open.
  while (window.isOpen())
    {
        
        while (gameState == "setupNewGame"){
        // ***** create new level from title screen
            
            // reset player position
            
            
            screen.deleteGameObjects();
            screen.populateEnemies(20);
            
            
            gameState = "inGame";
        }
        
        
        while (gameState == "title"){
//            screen.deleteGameObjects();
//            screen.populateEnemies(20);
            // must be included in each state
            // ******
            
            // clear window from previous frame, check that
            // window is not closed
            screen.windowCheckAndClear(window);
            if (!window.isOpen()){
                gameState = "exit";
            }
            // ******* end of must be included in each state

            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                gameState = "setupNewGame";
            }
            
            window.display();
        }  // end while (gameState == "title");
        
    
    while (gameState == "inGame"){
      // ***** required for each state
        
      // Check all the window's events that were triggered since the last iteration of the loop
        screen.windowCheckAndClear(window);
        if (!window.isOpen()){
            gameState = "exit";
        }

        screen.updateEnemies(window);
        screen.keyBoardPressed(window);
        screen.updateEnemyBullets(window);
        screen.updateBullets(window);
//        screen.updateExplosion(window);
        screen.updateEnemies(window);
        screen.shotCounter --;
        screen.updateGameStatistic(window);
    // allow player to quit
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
            gameState = "title";
        }
        
        
      // end the current frame
      window.display();
    } // end while(gameState = "inGame";
    }

    while(gameState == "exit"){
        return 0;
    }
}
