#include <iostream>
#include <format>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "App/Core/Game.hpp"
#include "App/Core/Text.hpp"
#include "App/UI/SdlFactory.hpp"
#include "App/Utils/Delay.hpp"
#include "App/Utils/Logger.hpp"
#include "App/Utils/Random.hpp"

// Used namespaces
using namespace App::Core;
using namespace App::UI;
using namespace App::Utils;
using Key_t = SdlFactory::Key_t;

// Constants
const int SCREEN_WIDTH  = 700;
const int SCREEN_HEIGHT = 700;

// Utility instances
Delay  instanceDelay;
Logger instanceLogger;
Random instanceRandom;

// Global variables
Key_t key              = Key_t::KEY_none;
int   playerSpeedX     = 2;
int   playerSpeedY     = 2;
int   velYEnemy        = 1;
int   velScore         = 50;
int   timerCounter     = 0;
int   level            = 0;
int   waitMs           = 4;
bool  skipRoundCreator = false;
bool  rocketLaunched   = false;

// ######################################################################
// # Media loading
// ######################################################################

Text*      txtInfo;
Text*      txtScore;
Image*     imgStart;
Image*     imgInstructions;
Image*     imgRoad;
Image*     imgLife;
Image*     imgRocket;
Image*     imgRocketLive;
PlayerCar* player;

typedef struct {
    Image* imgEnemy;
    bool   inUse;
} enemy_t;

enemy_t enemies[8];

static void loadMedia(Factory* factory) {
    txtInfo         = factory->getNewText("media/fonts/Iron & Brine.ttf", 144, "0", 255, 255, 255);
    txtScore        = factory->getNewText("media/fonts/Iron & Brine.ttf", 36, "00000", 255, 255, 255);
    imgStart        = factory->getNewImage("media/images/startscreen.bmp");
    imgInstructions = factory->getNewImage("media/images/instructions.bmp");
    imgRoad         = factory->getNewImage("media/images/road.bmp");
    imgLife         = factory->getNewImage("media/images/life.bmp");
    imgRocket       = factory->getNewImage("media/images/rocket.bmp");
    imgRocketLive   = factory->getNewImage("media/images/rocket.bmp");
    player          = factory->getNewPlayerCar("media/images/player_car.png");
    for (int i = 0; i < 8; i++) {
        enemies[i].imgEnemy = factory->getNewImage("media/images/enemy_car.png");
    }
}

// ######################################################################
// # Rendering - Components
// ######################################################################

static void renderRoad(void) {
    int y = imgRoad->y;
    imgRoad->visualize();
    imgRoad->y = y - SCREEN_HEIGHT;
    imgRoad->visualize();
    imgRoad->y = y;
}

static void renderScore(void) {
    txtScore->setText(std::format("{:05}", player->score), 255, 255, 255);
    txtScore->setScorePosition(SCREEN_WIDTH, txtScore->getWidth());
    txtScore->visualize();
}

static void renderRemainingLives(void) {
    imgLife->y = 45;
    for (int i = 0; i < 3; i++) {
        if (player->getNumOfLives() <= i) continue;
        imgLife->x = SCREEN_WIDTH - 35 - (i * 45);
        imgLife->visualize();
    }
}

static void renderRemainingRockets(void) {
    for (int i = 0; i < 10; i++) {
        if (player->getNumOfRockets() <= i) continue;
        imgRocket->y = (i < 5) ? 85 : 140;
        imgRocket->x = SCREEN_WIDTH - 25 - ((i % 5) * 15);
        imgRocket->visualize();
    }
}

static void renderEnemies(void) {
    for (int i = 0; i < 8; i++) {
        if (enemies[i].inUse) enemies[i].imgEnemy->visualize();
    }
}

static void renderLaunchedRocket(void) {
    if (!rocketLaunched) return;
    imgRocketLive->visualize();
}

// ######################################################################
// # Rendering - Windows
// ######################################################################

static void renderWindowSplash(Factory* factory) {
    factory->clear();
    imgStart->visualize();
    factory->update();
    instanceLogger.log("Window splash rendered");
    instanceDelay.wait(2000);
}

static void renderWindowInstructions(Factory* factory) {
    factory->clear();
    imgInstructions->visualize();
    factory->update();
    instanceLogger.log("Window instructions rendered");
    instanceDelay.wait(2000);
}

static void renderWindowGame(void) {
    renderRoad();
    renderScore();
    renderRemainingLives();
    renderRemainingRockets();
    renderEnemies();
    renderLaunchedRocket();
    player->visualize();
}

static void renderWindowGameOver(Factory* factory) {
    factory->clear();
    txtInfo->setText(std::format("{:05}", player->score), 255, 255, 255);
    txtInfo->setCenter(SCREEN_WIDTH, SCREEN_HEIGHT, txtInfo->getWidth(), txtInfo->getHeight());
    imgStart->visualize();
    txtInfo->visualize();
    factory->update();
}

// ######################################################################
// # Reset parameters
// ######################################################################

static void reset(void) {
    key              = Key_t::KEY_none;
    timerCounter     = 0;
    imgRoad->y       = 0;
    skipRoundCreator = false;
    rocketLaunched   = false;
    player->reset();
    for (int i = 0; i < 8; i++) {
        enemies[i].inUse = false;
    }
}

static void resetEnemies(void) {
    for (int i = 0; i < 8; i++) {
        if (enemies[i].inUse && enemies[i].imgEnemy->y <= SCREEN_HEIGHT) continue;
        enemies[i].imgEnemy->x    = 0;
        enemies[i].imgEnemy->y    = 0;
        enemies[i].imgEnemy->velY = 0;
        enemies[i].inUse          = false;
    }
}

static void resetRocket(void) {
    if (imgRocketLive->y >= -45 && rocketLaunched) return;
    imgRocketLive->x    = 0;
    imgRocketLive->y    = 0;
    imgRocketLive->velY = 0;
    rocketLaunched      = false;
}

// ######################################################################
// # Level changing
// ######################################################################

static void updateLevelNext(int levelNew, int velScore, int velRoad, int velXPlayer, int velYPlayer, int velYEnemy, int waitMsNew) {
    if (level != levelNew) instanceLogger.log("Level " + std::to_string(levelNew) + " reached");
    level         = levelNew;
    velScore      = velScore;
    imgRoad->velY = velRoad;
    playerSpeedX  = velXPlayer;
    playerSpeedY  = velYPlayer;
    velYEnemy     = velYEnemy;
    waitMs        = waitMsNew;
    // Adjust enemy speed
    for (int i = 0; i < 8; i++) {
        if (enemies[i].inUse && enemies[i].imgEnemy->velY) enemies[i].imgEnemy->velY = velYEnemy;
    }
}

static void updateLevel(void) {
    if (player->score <= 50) {
        updateLevelNext(0, 50, 2, 2, 2, 1, 4); // Level 0
    } else if (player->score > 50 && player->score <= 150) {
        updateLevelNext(1, 30, 3, 2, 2, 2, 5); // Level 1
    } else if (player->score > 150 && player->score <= 250) {
        updateLevelNext(2, 20, 4, 2, 2, 3, 5); // Level 2
    } else {
        updateLevelNext(3, 5, 5, 3, 3, 4, 12); // Level 3
    }
    if (player->velX < 0) player->velX = playerSpeedX * -1;
    if (player->velX > 0) player->velX = playerSpeedX;
    if (player->velY < 0) player->velY = playerSpeedY * -1;
    if (player->velY > 0) player->velY = playerSpeedY;
}

// ######################################################################
// # Generate entities
// ######################################################################

static void generateRocket(void) {
    if (player->rockets <= 0) return;
    if (rocketLaunched) return;
    instanceLogger.log("Rocket launched by player");
    rocketLaunched = true;
    player->decrementRocket();
    imgRocketLive->x    = player->x + 33 - 5;
    imgRocketLive->y    = player->y + 34 - 2;
    imgRocketLive->velY = -8;
}

static int getLaneX(int lane) {
    switch (lane) {
    case 0:
        return 149;
    case 1:
        return 228;
    case 2:
        return 308;
    case 3:
        return 387;
    default:
        return 471;
    }
}

static void generateEnemies(void) {

    resetEnemies();

    if (player->score % waitMs) return;

    if (skipRoundCreator) {
        skipRoundCreator = false;
        return;
    }

    int numOfEnemies = 0;
    int num          = instanceRandom.getRand(10);

    if (level == 0) {
        // 80% for 1 enemy, 20% for 2 enemies
        numOfEnemies = (num < 8) ? 1 : 2;
    } else if (level == 1) {
        // 70% for 1 enemy, 30% for 2 enemies
        numOfEnemies = (num < 7) ? 1 : 2;
    } else if (level == 2) {
        // 70% for 1 enemy, 20% for 2 enemies, 10% for 3 enemies
        if (num < 7) {
            numOfEnemies = 1;
        } else if (num >= 7 && num < 9) {
            numOfEnemies = 2;
        } else {
            numOfEnemies = 3;
        }
    } else if (level == 3) {
        // 50% for 1 enemy, 30% for 2 enemies, 20% for 3 enemies
        if (num < 5) {
            numOfEnemies = 1;
        } else if (num >= 5 && num < 8) {
            numOfEnemies = 2;
        } else {
            numOfEnemies = 3;
        }
    }

    bool laneUsed[5] = {false, false, false, false, false};
    for (int i = 0; i < 8; i++) {
        if (!numOfEnemies) break;
        if (enemies[i].inUse) continue;
        int lane = instanceRandom.getRand(5);
        while (laneUsed[lane]) {
            lane = (lane + 1) % 5;
        }
        enemies[i].imgEnemy->x    = getLaneX(lane);
        enemies[i].imgEnemy->y    = enemies[i].imgEnemy->getHeight() * -1;
        enemies[i].imgEnemy->velY = velYEnemy;
        enemies[i].inUse          = true;
        laneUsed[lane]            = true;
        numOfEnemies--;
    }
}

// ######################################################################
// # Update entities
// ######################################################################

static void updateRoad(void) {
    int y = imgRoad->y;
    y     = y + imgRoad->velY;
    if (y >= SCREEN_HEIGHT) y = y - SCREEN_HEIGHT;
    imgRoad->y = y;
}

static void updateScore(void) {
    if (timerCounter >= velScore) {
        timerCounter  = 0;
        player->score = player->score + 1;
        generateEnemies();
    } else {
        timerCounter = timerCounter + 1;
    }
}

// ######################################################################
// # Check collisions for rockets and vehicles
// ######################################################################

static bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2) {
    if ((x1 < (x2 + w2)) && ((x1 + w1) > x2) && (y1 < (y2 + h2)) && ((h1 + y1) > y2)) return true; // Collision!
    return false;
}

static void checkCollisions(void) {
    for (int i = 0; i < 8; i++) {
        if (!enemies[i].inUse) continue;
        // clang-format off
        // Image* p = player;
        Image* e = enemies[i].imgEnemy;
        Image* r = imgRocketLive;
        // Check collision enemy
        if (collision((player->x + 33), player->y, 6, 20, (e->x + 31), e->y, 8, 50) || \
            collision((player->x + 33), player->y, 6, 20, e->x, (e->y + 50), e->getWidth(), 134) || \
            collision(player->x, (player->y + 20), player->getWidth(), 125, (e->x + 31), e->y, 8, 50) || \
            collision(player->x, (player->y + 20), player->getWidth(), 125, e->x, (e->y + 50), e->getWidth(), 134)) {
            instanceLogger.log("Collision with enemy " + std::to_string(i));
            player->decrementLive();
            enemies[i].inUse = false;
        }
        // Check collision rocket
        if (collision((r->x + 5), (r->y + 2), 7, 43, (e->x + 31), e->y, 8, 50) || \
            collision((r->x + 5), (r->y + 2), 7, 43, e->x, (e->y + 50), e->getWidth(), 134)) {
            instanceLogger.log("Rocket hit enemy " + std::to_string(i));
            player->score = player->score + 20;
            skipRoundCreator = true;
            rocketLaunched   = false;
            enemies[i].inUse = false;
        }
        // clang-format on
    }
    resetEnemies();
    resetRocket();
}

// ######################################################################
// # Handle keyboard events
// ######################################################################

static void handleKeyEvent(void) {
    if (key == Key_t::KEY_UP_PRESSED || key == Key_t::KEY_DOWN_RELEASED) {
        player->velY = player->velY - playerSpeedY;
    } else if (key == Key_t::KEY_UP_RELEASED || key == Key_t::KEY_DOWN_PRESSED) {
        player->velY = player->velY + playerSpeedY;
    } else if (key == Key_t::KEY_LEFT_PRESSED || key == Key_t::KEY_RIGHT_RELEASED) {
        player->velX = player->velX - playerSpeedX;
    } else if (key == Key_t::KEY_LEFT_RELEASED || key == Key_t::KEY_RIGHT_PRESSED) {
        player->velX = player->velX + playerSpeedX;
    }
}

// ######################################################################
// # Game loops
// ######################################################################

static void startGameCountdown(Factory* factory, bool resume) {
    for (int i = 51; i > 48; i--) {
        char              num = (char)i;
        std::stringstream ss;
        ss << num;
        instanceLogger.log("Count down " + ss.str());
        txtInfo->setText(ss.str(), 255, 255, 255);
        txtInfo->setCenter(SCREEN_WIDTH, SCREEN_HEIGHT, txtInfo->getWidth(), txtInfo->getHeight());
        factory->clear();
        resume ? renderWindowGame() : imgStart->visualize();
        txtInfo->visualize();
        factory->update();
        instanceDelay.wait(1000);
    }
}

static bool loopGamePaused(Factory* factory) {

    factory->clear();
    renderWindowGame();
    txtInfo->setText("PAUZE", 255, 255, 255);
    txtInfo->setCenter(SCREEN_WIDTH, SCREEN_HEIGHT, txtInfo->getWidth(), txtInfo->getHeight());
    txtInfo->visualize();
    factory->update();

    while (true) {
        key = factory->eventHandler();
        if (key == Key_t::KEY_Q) {
            instanceLogger.log("Game ended by user");
            return false;
        } else if (key == Key_t::KEY_P) {
            instanceLogger.log("Game resuming...");
            break;
        }
    }

    startGameCountdown(factory, true);
    return true;
}

static bool loopGameOver(Factory* factory) {
    while (true) {
        key = factory->eventHandler();
        if (key == Key_t::KEY_Q) {
            instanceLogger.log("Game ended with score: " + std::to_string(player->score));
            return false;
        } else if (key == Key_t::KEY_R) {
            instanceLogger.log("Replaying game...");
            return true;
        }
    }
}

// ######################################################################
// # Public
// ######################################################################

Game::Game(Factory* factory) {
    this->factory = factory;
}

int Game::start() {

    if (!factory->init()) return -1;
    if (!factory->show("BATTLE TANK", SCREEN_WIDTH, SCREEN_HEIGHT)) return -2;

    instanceLogger.log("##################################################");
    instanceLogger.log("# BATTLE TANK - Game started");
    instanceLogger.log("##################################################");

    loadMedia(factory);

    renderWindowSplash(factory);
    renderWindowInstructions(factory);

    imgStart->modulateColor(80, 80, 80);

    // Run program
    while (true) {

        reset();
        startGameCountdown(factory, false);

        // Run game
        while (true) {

            updateLevel();
            // TODO - Build upper score limit (Game won)

            checkCollisions();

            if (player->getNumOfLives() < 0) {
                instanceLogger.log("Game over");
                break;
            }

            key = factory->eventHandler();
            if (key == Key_t::KEY_Q) {
                instanceLogger.log("Game stopped by user");
                break;
            } else if (key == Key_t::KEY_SPACE) {
                generateRocket();
            } else if (key == Key_t::KEY_P) {
                instanceLogger.log("Game paused");
                if (!loopGamePaused(factory)) break;
            } else {
                handleKeyEvent();
            }

            player->move(5, 475, 545, 150);
            for (int i = 0; i < 8; i++) {
                enemies[i].imgEnemy->move();
            }
            imgRocketLive->move();
            updateRoad();
            updateScore();

            // Update frequency
            instanceDelay.wait(20);

            // Render game window
            factory->clear();
            renderWindowGame();
            factory->update();
        }

        // Game over
        renderWindowGameOver(factory);
        if (!loopGameOver(factory)) break;
    }

    // Game quit
    return 0;
}
