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

int main()
{
    // gameState is used to control different 'states' of game
    // title, game setup, in game
    // title is the default starting 'state
    std::string gameState = "title";
    
    // initiate screen elements.
    Screen screen;
    sf::RenderWindow window(sf::VideoMode(screen.windowWidth, screen.windowHeight), "Space Invaders");
    window.setFramerateLimit(60);

  // Run the program as long as the main window is open.
  while (window.isOpen()){
        // default starting game state:
        // this loop is title screen
        // display title, wait for player to press start
        // to initiate actual game
        while (gameState == "title"){
            // clear window from previous frame, check that
            // window is not closed
            screen.windowCheckAndClear(window);
            if (!window.isOpen()){
                gameState = "exit";
            }
            // draw text 'space invaders'
            // draw text 'press space to start'
            window.draw(screen.welcomeText);
            window.draw(screen.instructionText);
            // wait for player to press start
            // once pressed move state to setupNameGame loop
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                gameState = "setupNewGame";
            }
            window.display();
        }
        
        // this loop sets up new game
        // deletes any leftover enemies, bullets, etc
        // populates new game with necessary objects
        if (gameState == "setupNewGame"){
            screen.deleteGameObjects();
            // now populate new objects for level
            screen.populateEnemies();
            // once done setting up, change gameState to inGame, ready to play
            gameState = "inGame";
        }
        
        // actual playing game loop
        while (gameState == "inGame"){
          // Check all the window's events that were triggered since the last iteration of the loop
            screen.windowCheckAndClear(window);
            if (!window.isOpen()){
                gameState = "exit";
            }

            // each iteration update enemies
            screen.updateEnemies(window);
            screen.updateEnemyBullets(window);
            screen.updateBullets(window);
            
            // check for player keyboard inputs
            screen.keyBoardPressed(window);
            // update limit to be able to shoot again
            screen.shotCounter --;

            // update data printed to screen: score, elvel
            screen.updateGameStatistic(window);
            
            // allow player to quit
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
                screen.gameOverReset(gameState, window);
            }
            
            // if any conditions are met for game over
            // ie: player hit by bullet
            // or: enemies too low
            if (screen.gameOver == true){
                screen.gameOverReset(gameState, window);
            }
            
            // end the current frame
            window.display();
        }
    }

    // if user hits 'x' on window during any gameState
    // this allows you to exit
    if(gameState == "exit"){
        return 0;
    }
}
