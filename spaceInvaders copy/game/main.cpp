#include <SFML/Graphics.hpp>

#include <math.h>
#include <iostream>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include <vector>

std::vector<Enemy> populateEnemy(int number){
    float xSpace = 75;
    float ySpace = 75;
    float xStart = 250;
    float yStart = 250;
    std::vector<Enemy> enemies;
    for (int row = 0; row <= 4; row++){
        for (int col = 0; col <= 5; col++){
            Enemy newEnemy(xStart, yStart);
            // need to set the Rect bounding box to start position as well
            newEnemy.enemyBox.setPosition(xStart, yStart);
            xStart += xSpace;
            enemies.push_back(newEnemy);
        }
        xStart = 250;
        yStart += ySpace;
    }
    return enemies;
}

float playerX = 600;

int main()
{
    const int windowWidth = 1200;
    const int windowHeight = 1200;
    const int moveSpeed = 10;
    // start with shot counter ready to allow player to shoot
    // when bullet fires, set to positive value
    // constantly --, then when value is <0 allow another
    // bullet to be fire
    int shotCounter = 0;
  // Create the main program window.
  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "My window");
    window.setFramerateLimit(60);

//  float angle = 0.0;
    Player player;
    std::vector<Enemy> enemies = populateEnemy(20);
    
    // create a bullet off screen to allow code checking for bullets to execute,
    // return false if needed
    // shouldcreate isAlive bool for bullet
    std::vector<Bullet> bullets;
    // create off screen bullet
    Bullet bullet(player.getXPos() - 9999);
    bullets.push_back(bullet);
    
    

  // Run the program as long as the main window is open.
  while (window.isOpen())
    {
      // Check all the window's events that were triggered since the last iteration of the loop
      sf::Event event;
      while (window.pollEvent(event))
        {
          // "close requested" event: we close the window
          if (event.type == sf::Event::Closed) {
            window.close();
          }
        }

      // clear the window with black color
      window.clear(sf::Color::Black);

        // check keyboard inputs
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) ){
            player.updatePos(player.getXPos() + moveSpeed);
            if (player.getXPos() > windowWidth - 65){
                player.updatePos(player.getXPos() - moveSpeed);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            player.updatePos(player.getXPos() - moveSpeed);
            if (player.getXPos() < 0){
                player.updatePos(player.getXPos() + moveSpeed);
            }
        }
        
        // fire bullets
        // if space is pressed, and its been long enough since last bullet has been shot
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (shotCounter < 0) ){
            Bullet bullet(player.getXPos());
            bullets.push_back(bullet);
            // higher values slow down rate of fire
            shotCounter = 30;
        }
        
        shotCounter --;
        player.playerImage.setPosition(player.xPos, player.yPos);
        
        // only if enemy is alive draw and update
        for (Enemy enemy : enemies){
            if (enemy.isAlive){
                enemy.enemyImage.setPosition(enemy.xPos, enemy.yPos);
                window.draw(enemy.enemyImage);
            }
        }
        
        window.draw(player.playerImage);
        
        // update bullets
        // nested loop to check for each bullet if collision with each
        // enemy
        for (int i = 0; i < bullets.size(); i++){
            if (bullets[i].isAlive){
                window.draw(bullets[i].bulletImage);
                bullets[i].bulletImage.setPosition(bullets[i].getXPos(), bullets[i].updateYPos());
            }
            // get the bounding box for collision from bullet
            sf::FloatRect bulletBox = bullets[i].bulletImage.getGlobalBounds();
            // nested loop for each enemy to check against each bullet
            for (int j = 0; j < enemies.size(); j++){
                // get the bounding box for enemy
                sf::FloatRect enemyBox = enemies[j].enemyBox.getGlobalBounds();
                
                if (bulletBox.intersects(enemyBox) && enemies[j].isAlive && bullets[i].isAlive){
                    enemies[j].isAlive = false; // enemy killed
                    bullets[i].isAlive = false;
                }
            }
        }

      // end the current frame
      window.display();
    }

  return 0;
}
