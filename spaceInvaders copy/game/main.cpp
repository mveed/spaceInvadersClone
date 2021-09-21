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

/*
std::vector<Enemy> populateEnemy(int number){
    float xSpace = 150;
    float ySpace = 75;
    float xStart = 150;
    float yStart = 150;
    std::vector<Enemy> enemies;
    for (int row = 0; row <= 4; row++){
        for (int col = 0; col <= 5; col++){
            Enemy newEnemy(xStart, yStart);
            // need to set the Rect bounding box to start position as well
            newEnemy.enemyBox.setPosition(xStart, yStart);
            xStart += xSpace;
            enemies.push_back(newEnemy);
        }
        xStart = 150;
        yStart += ySpace;
    }
    return enemies;
}
 */

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
    const int windowWidth = 1200;
    const int windowHeight = 1200;
    const int moveSpeed = 10;
    
    // start with shot counter ready to allow player to shoot
    // when bullet fires, set to positive value
    // constantly --, then when value is <0 allow another
    // bullet to be fire
    int shotCounter = 0;
  // Create the main program window.


//  float angle = 0.0;
    Player player;
    
    Screen screen;
    
//    std::vector<Enemy> screen.enemies = screen.screen.enemies;
    
    // create a bullet off screen to allow code checking for bullets to execute,
    // return false if needed
    // shouldcreate isAlive bool for bullet
    std::vector<Bullet> bullets;
    // create off screen bullet
    Bullet bullet(player.getXPos() - 9999);
    bullets.push_back(bullet);
    
    float turningDistance = 0;
    float enemiesKilled = 0;
    float distance = 1;
    
    
    std::string fontsFile = "GrechenFuemen-Regular.ttf";
    sf::Font grechenFuemen;
    grechenFuemen.loadFromFile(fontsFile);
    sf::Text text;
    generateText(text, grechenFuemen, "234");

    
    // create off screen enemyBullet, same as above for bullet
    std::vector<EnemyBullet> enemyBullets;
    EnemyBullet enemyBullet(-9999, -9999);
    enemyBullets.push_back(enemyBullet);
    
    // create off screen explosion
    std::vector<Explosion> explosions;
    Explosion explosion(-9999, -9999);
    explosions.push_back(explosion);
    
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "My window");
      window.setFramerateLimit(60);
    
    

  // Run the program as long as the main window is open.
  while (window.isOpen())
    {
        
        while (gameState == "setupNewGame"){
        // ***** create new level from title screen
            
            // reset player position
            player.xPos = 600;
            player.yPos = 1100;
            
            screen.deleteGameObjects(screen.enemies, enemyBullets, bullets, explosions);
            
            // recreate stuff
            // create off screen enemyBullet, same as above for bullet
            EnemyBullet enemyBullet(-9999, -9999);
            enemyBullets.push_back(enemyBullet);
            
            // create off screen explosion
            Explosion explosion(-9999, -9999);
            explosions.push_back(explosion);
            
            screen.populateEnemies(20);
            
            // create a bullet off screen to allow code checking for bullets to execute,
            // return false if needed
            // shouldcreate isAlive bool for bullet

            // create off screen bullet
            Bullet bullet(player.getXPos() - 9999);
            bullets.push_back(bullet);
            
            gameState = "inGame";
        }
        
        
        while (gameState == "title"){
            
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

        

      // ***** end of required for each state

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
            Bullet bullet(player.getXPos() + 30);
            bullets.push_back(bullet);
            // higher values slow down rate of fire
            shotCounter = 30;
        }
        
        shotCounter --;
        player.playerImage.setPosition(player.xPos, player.yPos);
        
        // only if enemy is alive draw and update
        bool hitBoarder = std::any_of(screen.enemies.begin(), screen.enemies.end(), [](Enemy en) -> bool { return en.getXPos() >= 1180 || en.getXPos() <= 10;});
        if (hitBoarder) {
            distance = -distance;
            turningDistance = 20;
        } else {
            turningDistance = 0;
        }
        
        for (Enemy & enemy : screen.enemies){
            if (enemy.isAlive){
                window.draw(enemy.enemyImage);
                enemy.enemyImage.setPosition(enemy.updateXPos(distance), enemy.updateYPos(turningDistance));
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
            for (int j = 0; j < screen.enemies.size(); j++){
                // get the bounding box for enemy
                sf::FloatRect enemyBox = screen.enemies[j].enemyBox.getGlobalBounds();
                
                if (bulletBox.intersects(enemyBox) && screen.enemies[j].isAlive && bullets[i].isAlive){
                    screen.enemies[j].isAlive = false; // enemy killed
                    bullets[i].isAlive = false;
                    // create explosion where enemy was killed
                    Explosion explosion(screen.enemies[j].getXPos(), screen.enemies[j].getYPos());
                    explosions.push_back(explosion);
                    enemiesKilled += 1;
                    if (distance < 0) {
                        distance = -1 -(enemiesKilled / 5);
                    } else {
                        distance = 1 + (enemiesKilled / 5);
                    }
                }
            }
        }
        text.setPosition(100, 100);
        window.draw(text);
        // **** ill put enemy bullet code here
        
        // use random number to determine when to fire bullet
        // if returns true, create a new bullet at enemy position
        // create it inside enemyBullets vector
        for (int i = 0; i < screen.enemies.size(); i++)
        if (randomizeEnemyBullets() && screen.enemies[i].isAlive){
            EnemyBullet enemyBullet(screen.enemies[i].getXPos() + 20, screen.enemies[i].getYPos()+ 25);
            enemyBullets.push_back(enemyBullet);
        }

        // iterate through each bullet, if its alive, check for collision with player update the position
        // and draw as well
        for (int i = 0; i < enemyBullets.size(); i++){
            if (enemyBullets[i].isAlive){
                // get the bounding box for collision from enemy bullet and player
                sf::FloatRect enemyBulletBox = enemyBullets[i].enemyBulletImage.getGlobalBounds();
                sf::FloatRect playerBox = player.playerImage.getGlobalBounds();
                
                // should add && to if for player.isAlive bool
                if (playerBox.intersects(enemyBulletBox)){
                    enemyBullets[i].isAlive = false;
                    std::cout << "Player hit. \n";
                }
                    
                // position and draw update
                enemyBullets[i].enemyBulletImage.setPosition(enemyBullets[i].getXPos(), enemyBullets[i].updateYPos());
                window.draw(enemyBullets[i].enemyBulletImage);
            }
        }
        // **** end enemy bullet code

        // **** begin explosion code
        for (int i = 0; i < explosions.size(); i++){
            explosions[i].update();
            if (explosions[i].isAlive){
                explosions[i].explosionImage.setPosition(explosions[i].getXPos(), explosions[i].getYPos());
                window.draw(explosions[i].explosionImage);
            }
        }
        // **** end explosion code
        
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
