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
    text.setFont(font);
    text.setString(str); // set the character size
    text.setCharacterSize(48); // in pixels, not points!
    text.setFillColor(sf::Color::Red);
    // set the text style
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
}

float playerX = 600;

int main()
{



    
    
    std::string fontsFile = "GrechenFuemen-Regular.ttf";
    sf::Font grechenFuemen;
    grechenFuemen.loadFromFile(fontsFile);
    sf::Text text;
    generateText(text, grechenFuemen, "234");
    
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
            screen.deleteGameObjects();
            screen.populateEnemies(20);
            // must be included in each state
            // ******
            sf::Event event;
            while (window.pollEvent(event))
              {
                // "close requested" event: we close the window
                if (event.type == sf::Event::Closed) {
                    gameState = "exit";
                  window.close();
                }
              }

            // clear the window with black color
            window.clear(sf::Color::Black);
            // ******* end of must be included in each state
    
            sf::RectangleShape titleSquare(sf::Vector2f(1000, 150));
            titleSquare.setFillColor(sf::Color(200, 200, 200));
            titleSquare.setPosition(100, 150);
            
            sf::RectangleShape titleSquare2(sf::Vector2f(800, 150));
            titleSquare2.setFillColor(sf::Color(200, 200, 200));
            titleSquare2.setPosition(200, 950);
            
            window.draw(titleSquare);
            window.draw(titleSquare2);
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                gameState = "setupNewGame";
            }
            
            window.display();
        }  // end while (gameState == "title");
        
    
    while (gameState == "inGame"){
      // ***** required for each state
        
      // Check all the window's events that were triggered since the last iteration of the loop
      sf::Event event;
      while (window.pollEvent(event)) {
          text.setPosition(100, 100);
          window.draw(text);
          // "close requested" event: we close the window
          if (event.type == sf::Event::Closed) {
              gameState = "exit";
            window.close();
          }
        }

      // clear the window with black color
        window.clear(sf::Color::Black);

        screen.updateEnemies(window);
        screen.keyBoardPressed(window);
        screen.updateEnemyBullets(window);
        screen.updateBullets(window);
        screen.updateEnemies(window);
        screen.updateExplosion(window);
        screen.shotCounter --;
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
