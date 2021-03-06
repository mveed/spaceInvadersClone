//
//  Screen.cpp
//  game
//
//  Created by Xiaojun Wu on 9/21/21.
//

#include "Screen.hpp"

const std::string resourceDir_ = "../documents/";

Screen::Screen() {
    // populate player, enemies
    populateEnemies();
    
    // create off screen playerBullet enemyBullet & explosion for the window to draw.
    Bullet playerBulletOffScreen(player.getXPos() - 9999);
    playerBullets.push_back(playerBulletOffScreen);
    EnemyBullet enemyBullet(-9999, -9999);
    enemyBullets.push_back(enemyBullet);
    Explosion explosion(-9999, -9999);
    explosions.push_back(explosion);


    std::string fontFile = resourceDir_ + "StickNoBills-ExtraLight.ttf";
    gameFont.loadFromFile(fontFile);

    // intiate the statistic text and the welcome text needed for the game.
    scoreText = createTextTitleScreen(scoreText, 50, 50, 48);
    levelText = createTextTitleScreen(levelText, windowWidth-300, 50, 48);
    gameOverText = createTextTitleScreen(gameOverText, windowWidth/2 - 190, windowHeight - 800, 92);
    welcomeText = createTextTitleScreen(welcomeText, windowWidth/4, windowHeight - 900, 150);
    welcomeText.setString("Space Invaders");
    instructionText = createTextTitleScreen(instructionText, windowWidth/4, windowHeight - 600, 100);
    instructionText.setString("Press Space To Defend");
}

void Screen::populateEnemies() {
    // populate 20 enemy/invaders for the game and adds space between invaders;
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
     // delete all enemies & bullets & enemyBullets before starting a new game.
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
    // updates enemies positing on the screen;
    // if any enemy in hits the boarder will flip the moving direction for the entire team and move to lower.
    for (Enemy & enemy : enemies) {
        turningDistance = 0;
        if ((enemy.getXPos() >= windowWidth - 50 || enemy.getXPos() <= 10) && enemy.isAlive) {
            distance = -distance;
            turningDistance = 20;
            break;;
        }
    }
    
    // reder enemy image and update the enemy position.
    for (Enemy & enemy : enemies){
        if (enemy.isAlive){
            // getting ready to load texture and filename
            sf::Texture imageFile;
            std::string fileName;

            //std::string fontFile = resourceDir_ + "StickNoBills-ExtraLight.ttf";
            // alienType is int set randomly for each row when enemy created
            // used to set rows with same image for aliens
            if (enemy.alienType == 1){
                fileName = resourceDir_ + "alien5.png";
            }
            if (enemy.alienType == 2){
                fileName = resourceDir_ + "alien2.png";
            }
            if (enemy.alienType == 3){
                fileName = resourceDir_ + "alien4.png";
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
    //checking the playerBullet collision and update the game statistics.
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
            
            // if player bullet and an enemy collide, updae the game statistics and set up explosion and make the bullet disapear.
            if (bulletBox.intersects(enemyBox) && enemies[j].isAlive && playerBullets[i].isAlive){
                enemies[j].isAlive = false; // enemy killed
                playerBullets[i].isAlive = false;
                enemiesKilled += 1;
                if (enemies.size() == enemiesKilled){
                    levelUp();
                }
                updateDistance();
                setExplosion(j, window);
            }
        }
        
    }
}


// return a random number to generate the enemy bullet;
bool Screen::randomizeEnemyBullets(){
    int x = rand() % 10000;
    return (x > 9985);
}


void Screen::updateEnemyBullets(sf::RenderWindow & window) {
    // generate random enemy bullte and check if any enemy bullet collide with the player.
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
            }
            window.draw(enemyBullets[i].enemyBulletImage);
        }
    }
}

void Screen::keyBoardPressed(sf::RenderWindow & window) {
    // check keyboard event and moving/render the object accordingly or fire a bullet.
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
    std::string fileName = resourceDir_ + "player.png";
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
    // update game statistic when enemy was killed or level up the game.
    std::string scoreString = "Your Score: " + std::to_string(calculateScore());
    std::string levelString = "Game Level: " + std::to_string(gameLevel);
    
    scoreText.setString(scoreString);
    levelText.setString(levelString);
    
    window.draw(scoreText);
    window.draw(levelText);
    
}

int Screen::calculateScore() {
    // calculate the game score.
    return previousScore + enemiesKilled + enemiesKilled * gameLevel;
}


void Screen::updateDistance() {
    // update the distance according to the game level and the number of enemies killed.
    int sign = distance < 0 ? -1 : 1;
    distance = sign * gameLevel + sign *(enemiesKilled / 7);
}


void Screen::setExplosion(int enemyIdx, sf::RenderWindow & window) {
    // set up explosiong when the enemy was killed.
    // using the killed enemy's x and y position to set up explosion effect on the screen.
    int xPos = enemies[enemyIdx].getXPos();
    int yPos = enemies[enemyIdx].getYPos();
    Explosion  newExplosion(xPos, yPos);
    newExplosion.update();
    if (newExplosion.isAlive){
        // setup texture and file name
        sf::Texture imageFile;
        std::string fileName = resourceDir_ + "explosion.png";
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
    // level up the game and update the game statistics and player position accordingly.
    // reset or delete objects before starting a new game.
    previousScore = calculateScore();
    deleteGameObjects();
    populateEnemies();
    player.updatePos(600);
    gameLevel++;
    distance = gameLevel;
    enemiesKilled = 0;
}

void Screen::gameOverReset(std::string & gameState, sf::RenderWindow & window){
    // reset the game statistics when the game is over.
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

sf::Text Screen::createTextTitleScreen(sf::Text & text, int xPos, int yPos, int fontSize) {
    // create the text for the game to render.
    text.setFont(gameFont);
    text.setCharacterSize(fontSize); // in pixels, not points!
    text.setFillColor(sf::Color::Red); // set the text style
    text.setStyle(sf::Text::Bold);
    text.setPosition(xPos, yPos);
    return text;
}

// test to verify
void Screen::addDeleteObjectsTest(int vectorSize, int expectedValue, std::string errorMsg){
    if (vectorSize != expectedValue){
        std::cerr << errorMsg << " should equal " << expectedValue << ", instead returned " << vectorSize << "\n";
        exit(1);
    }
}
