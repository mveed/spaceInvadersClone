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
    
    std::string fontFile = "StickNoBills-ExtraLight.ttf";
    gameFont.loadFromFile(fontFile);

    scoreText.setFont(gameFont);
    scoreText.setCharacterSize(48); // in pixels, not points!
    scoreText.setFillColor(sf::Color::Red); // set the text style
    scoreText.setStyle(sf::Text::Bold);
    scoreText.setPosition(50, 50);
    
    levelText.setFont(gameFont);
    levelText.setCharacterSize(48); // in pixels, not points!
    levelText.setFillColor(sf::Color::Red); // set the text style
    levelText.setStyle(sf::Text::Bold);
    levelText.setPosition(windowWidth - 300, 50);
    
    gameOverText.setFont(gameFont);
    gameOverText.setCharacterSize(92); // in pixels, not points!
    gameOverText.setFillColor(sf::Color::Red); // set the text style
    gameOverText.setStyle(sf::Text::Bold);
    gameOverText.setPosition(windowWidth/2 - 190, windowHeight - 800);
}

void Screen::populateEnemies( int numEnemy ) {
    float xSpace = 150;
    float ySpace = 75;
    float xStart = 150;
    float yStart = 150;
    enemies = {};
    for (int row = 0; row <= 4; row++){
        int randNumber = rand() % 3 + 1;
        for (int col = 0; col <= 5; col++){
            Enemy newEnemy(xStart, yStart);
            newEnemy.alienType = randNumber;
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
    enemies = {};
    for (int i = 1; i < enemyBullets.size(); i++){
        enemyBullets.pop_back();
    }
    for (int i = 1; i < playerBullets.size(); i++){
        playerBullets.pop_back();
    }
    for (int i = 1; i < explosions.size(); i++){
        explosions.pop_back();
    }
}

void Screen::updateEnemies(sf::RenderWindow & window) {

//    bool hitBoarder = std::any_of(enemies.begin(), enemies.end(), [](Enemy en) -> bool { return en.getXPos() >=  1180 || en.getXPos() <= 10;});
    bool hitBoarder = false;
    for (Enemy & enemy : enemies) {
        turningDistance = 0;
        if (enemy.getXPos() >= windowWidth - 50 || enemy.getXPos() <= 10) {
            hitBoarder = true;
            distance = -distance;
            turningDistance = 20;
            break;;
        }
    }
    
    for (Enemy & enemy : enemies){
        if (enemy.isAlive){
            // getting ready to load texture and filename
            sf::Texture imageFile;
            std::string fileName;
            
            // alienType is int set randomly for each row when enemy created
            // used to set rows with same image for aliens
            if (enemy.alienType == 1){
                fileName = "alien1.png";
            }
            if (enemy.alienType == 2){
                fileName = "alien2.png";
            }
            if (enemy.alienType == 3){
                fileName = "alien3.png";
            }
            // test to make sure file opens
            if(!imageFile.loadFromFile(fileName)){
                std::cout << "Failed to load " << fileName;
                exit(9);
            }
            
            // set sprite as the image
            sf::Sprite alienSprite(imageFile);
            alienSprite.setScale(sf::Vector2f(5.f, 5.f));
            alienSprite.setPosition(enemy.xPos, enemy.yPos);
            // spriteTest.setColor(sf::Color(255, 0, 0));
            window.draw(alienSprite);
            enemy.enemyImage.setPosition(enemy.updateXPos(distance), enemy.updateYPos(turningDistance));
            if (enemy.getYPos() > windowHeight - 100){
                gameOver = true;
            }
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
                enemiesKilled += 1;
                updateDistance();

                setExplosion(j, window);
            }
        }
        if (enemies.size() == enemiesKilled){
            levelUp();
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
            enemyBullets[i].enemyBulletImage.setPosition(enemyBullets[i].getXPos(), enemyBullets[i].updateYPos());
            // get the bounding box for collision from enemy bullet and player
            sf::FloatRect enemyBulletBox = enemyBullets[i].enemyBulletImage.getGlobalBounds();
            player.playerImage.setPosition(player.getXPos(), player.yPos);
            sf::FloatRect playerBox = player.playerImage.getGlobalBounds();
            // should add && to if for player.isAlive bool
            if (playerBox.intersects(enemyBulletBox)){
                enemyBullets[i].isAlive = false;
                gameOver = true;
                std::cout << "Player hit. \n";
            }
                
            // position and draw update

            window.draw(enemyBullets[i].enemyBulletImage);
        }
    }
}

void Screen::updateExplosion(sf::RenderWindow & window) {
    for (int i = 0; i < explosions.size(); i++){
        explosions[i].update();
        if (explosions[i].isAlive){
            explosions[i].explosionImage.setPosition(explosions[i].getXPos(), explosions[i].getYPos());
            
            // setup texture and file name
            sf::Texture imageFile;
            std::string fileName = "explosion.png";
            // load file, test that it opens
            if(!imageFile.loadFromFile(fileName)){
                std::cout << "Failed to load " << fileName;
                exit(9);
            }
                
            // set sprite and draw
            sf::Sprite explosionSprite(imageFile);
            explosions[i].xPos += distance;
//            explosionSprite.setPosition(explosions[i].xPos, explosions[i].yPos);
            explosionSprite.setScale(sf::Vector2f(5.f, 5.f));
            // spriteTest.setColor(sf::Color(255, 0, 0));
            if (explosions[i].life > 3){
                explosionSprite.setColor(sf::Color(255, 0, 0));
            } else {
                explosionSprite.setColor(sf::Color(255, 255, 255));
            }
            explosionSprite.setPosition(explosions[i].getXPos(), explosions[i].getYPos());
            window.draw(explosionSprite);
//            window.draw(explosions[i].explosionImage);
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

    // setup texture and file name
    sf::Texture imageFile;
    std::string fileName = "player.png";
    // load file, test that it opens
    if(!imageFile.loadFromFile(fileName)){
        std::cout << "Failed to load " << fileName;
        exit(9);
    }
        
    // set sprite and draw
    sf::Sprite playerSprite(imageFile);
    playerSprite.setPosition(player.xPos, player.yPos);
    // spriteTest.setColor(sf::Color(255, 0, 0));
    window.draw(playerSprite);
}

void Screen::windowCheckAndClear(sf::RenderWindow & window){
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

}

void Screen::updateGameStatistic(sf::RenderWindow & window) {
    std::string scoreString = "Your Score: " + std::to_string(calculateScore());
    std::string levelString = "Game Level: " + std::to_string(gameLevel);
    
    scoreText.setString(scoreString);
    levelText.setString(levelString);
    
    window.draw(scoreText);
    window.draw(levelText);
    
}

int Screen::calculateScore() {
    
    return previousScore + enemiesKilled + enemiesKilled * gameLevel;
}


void Screen::updateDistance() {
    int sign = distance < 0 ? -1 : 1;
    distance = sign * gameLevel + sign *(enemiesKilled / 7);
}


void Screen::setExplosion(int idx, sf::RenderWindow & window) {
    int xPos = enemies[idx].getXPos();
    int yPos = enemies[idx].getYPos();
    Explosion  newExplosion(xPos, yPos);
    newExplosion.update();
    if (newExplosion.isAlive){
        // setup texture and file name
        sf::Texture imageFile;
        std::string fileName = "explosion.png";
        // load file, test that it opens
        if(!imageFile.loadFromFile(fileName)){
            std::cout << "Failed to load " << fileName;
            exit(9);
        }
        sf::Sprite explosionSprite(imageFile);
        
        explosionSprite.setScale(sf::Vector2f(5.f, 5.f));
        if (newExplosion.life > 3){
            explosionSprite.setColor(sf::Color(255, 0, 0));
        } else {
            explosionSprite.setColor(sf::Color(255, 255, 255));
        }
        explosionSprite.setPosition(xPos, yPos);
        window.draw(explosionSprite);
    }
    newExplosion.explosionImage.setPosition(xPos, yPos);
    window.draw(newExplosion.explosionImage);
}


void Screen::levelUp() {
    previousScore = calculateScore();
    deleteGameObjects();
    populateEnemies(20);
    player.updatePos(600);
    gameLevel++;
    distance = gameLevel;
    enemiesKilled = 0;
}

void Screen::gameOverReset(std::string & gameState, sf::RenderWindow & window){
    deleteGameObjects();
    enemiesKilled = 0;
    distance = 1;
    player.xPos = 1200*1.5/2;
    player.yPos = 1100;
    previousScore = 0;
    gameLevel = 1;
    int gameOverCounter = 120;
    while (gameOverCounter > 0){
        window.clear(sf::Color::Black);
        std::string gameOverString = "Game Over ";
        
        gameOverText.setString(gameOverString);
        
        window.draw(gameOverText);
        gameOverCounter --;
        window.display();
        
    }
    gameOver = false;
    gameState = "title";
}
