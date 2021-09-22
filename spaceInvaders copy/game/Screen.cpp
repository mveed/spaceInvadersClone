//
//  Screen.cpp
//  game
//
//  Created by Xiaojun Wu on 9/21/21.
//

#include "Screen.hpp"


Screen::Screen() { // populate player, enemies
    populateEnemies(20);
    
// create off screen playerBullet enemyBullet & explosion for the window to draw.
    Bullet playerBulletOffScreen(player.getXPos() - 9999);
    playerBullets.push_back(playerBulletOffScreen);
    
    EnemyBullet enemyBullet(-9999, -9999);
    enemyBullets.push_back(enemyBullet);
    
    Explosion explosion(-9999, -9999);
    explosions.push_back(explosion);
    
    
}

void Screen::populateEnemies( int numEnemy ) {
    float xSpace = 150;
    float ySpace = 75;
    float xStart = 150;
    float yStart = 150;
    enemies = {};
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
}

void Screen::deleteGameObjects(){
     // delete all enemies
            for (int i = 0; i < enemies.size(); i++){
                enemies.pop_back();
            }
            for (int i = 0; i < enemyBullets.size(); i++){
                enemyBullets.pop_back();
            }
            for (int i = 0; i < playerBullets.size(); i++){
                playerBullets.pop_back();
            }
            for (int i = 0; i < explosions.size(); i++){
                explosions.pop_back();
            }
}

void Screen::updateEnemies(sf::RenderWindow & window) {
    bool hitBoarder = std::any_of(enemies.begin(), enemies.end(), [](Enemy en) -> bool { return en.getXPos() >= 1180 || en.getXPos() <= 10;});
    if (hitBoarder) {
        distance = -distance;
        turningDistance = 20;
    } else {
        turningDistance = 0;
    }
    
    for (Enemy & enemy : enemies){
        if (enemy.isAlive){
            window.draw(enemy.enemyImage);
            enemy.enemyImage.setPosition(enemy.updateXPos(distance), enemy.updateYPos(turningDistance));
        }
    }
}

void Screen::updateBullets(sf::RenderWindow & window) {
    for (int i = 0; i < playerBullets.size(); i++){
        if (playerBullets[i].isAlive){
            window.draw(playerBullets[i].bulletImage);
            playerBullets[i].bulletImage.setPosition(playerBullets[i].getXPos(), playerBullets[i].updateYPos());
        }
        // get the bounding box for collision from bullet
        sf::FloatRect bulletBox = playerBullets[i].bulletImage.getGlobalBounds();
        // nested loop for each enemy to check against each bullet
        for (int j = 0; j < enemies.size(); j++){
            // get the bounding box for enemy
            sf::FloatRect enemyBox = enemies[j].enemyBox.getGlobalBounds();
            
            if (bulletBox.intersects(enemyBox) && enemies[j].isAlive && playerBullets[i].isAlive){
                enemies[j].isAlive = false; // enemy killed
                playerBullets[i].isAlive = false;
                // create explosion where enemy was killed
                Explosion explosion(enemies[j].getXPos(), enemies[j].getYPos());
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
}

bool Screen::randomizeEnemyBullets(){
    int x = rand() % 10000;
    return (x > 9985);
}

void Screen::updateEnemyBullets(sf::RenderWindow & window) {
    for (int i = 0; i < enemies.size(); i++)
    if (randomizeEnemyBullets() && enemies[i].isAlive){
        EnemyBullet enemyBullet(enemies[i].getXPos() + 20, enemies[i].getYPos()+ 25);
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
}

void Screen::updateExplosion(sf::RenderWindow & window) {
    for (int i = 0; i < explosions.size(); i++){
        explosions[i].update();
        if (explosions[i].isAlive){
            explosions[i].explosionImage.setPosition(explosions[i].getXPos(), explosions[i].getYPos());
            window.draw(explosions[i].explosionImage);
        }
    }
}

void Screen::keyBoardPressed(sf::RenderWindow & window) {
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
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && (shotCounter < 0) ){
        Bullet bullet(player.getXPos() + 30);
        playerBullets.push_back(bullet);
        // higher values slow down rate of fire
        shotCounter = 30;
    }
    
    window.draw(player.playerImage);
}
