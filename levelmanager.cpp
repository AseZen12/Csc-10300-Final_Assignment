#include "levelmanager.h"

using namespace std;

LevelManager::LevelManager(int initLevel, bool initState) {
     level = initLevel;
     isActive = initState;
}


void LevelManager::UpdateLevel(int levelNumber, Player* insertedPlayer) {

    //Level Check
    if(!isActive) {
       isActive = true; 
    }

    if(levelNumber == 1) {
        Level1();
    }
    else if(levelNumber == 2) {

    } 
    else if(levelNumber == 3) {
   
    }
     //Collision Detection
    Collision(level1_Platforms,level1_Enemy, insertedPlayer);
}

void LevelManager::Collision(vector<Platform> list, vector<Enemy> enemyList, Player* insertedPlayer) {
    Rectangle playerHitbox = insertedPlayer->GetHitBox();

    for (Platform& platform : list) {
        Rectangle platformHitbox = platform.GetHitBox();

        if (CheckCollisionRecs(playerHitbox, platformHitbox)) {
            Rectangle collision = GetCollisionRec(playerHitbox, platformHitbox);

            // Vertical collision resolution
            if (collision.width > collision.height) {
                if (playerHitbox.y < platformHitbox.y) {
                    // Player is above platform -> land on it
                    insertedPlayer->SetY(platformHitbox.y - playerHitbox.height);
                    insertedPlayer->SetY_Velocity(0);
                } else {
                    // Player hit the bottom of the platform (e.g. jumping)
                    insertedPlayer->SetY(platformHitbox.y + platformHitbox.height);
                    insertedPlayer->SetY_Velocity(0);
                }
            }
            // Horizontal collision resolution
            else if (collision.height >= collision.width) {
                if (playerHitbox.x < platformHitbox.x) {
                    // Player hit platform from the left
                    insertedPlayer->SetX(platformHitbox.x - playerHitbox.width);
                    insertedPlayer->SetX_Velocity(0);
                } else {
                    // Player hit platform from the right
                    insertedPlayer->SetX(platformHitbox.x + platformHitbox.width);
                    insertedPlayer->SetX_Velocity(0);
                }
            }
        }
    }
}

void LevelManager::InitLevel() {
    //Level Generation
    level1_Platforms.push_back(Platform(-100, 500, 50, 3000)); // First Barrier
    level1_Platforms.push_back(Platform(-7000, 500,12000, 500)); //Main Platform
    level1_Platforms.push_back(Platform(5000, 500, 500, 3000)); //Laster Barrier
    level1_Platforms.push_back(Platform(100, 250, 150, 25)); //First
    level1_Platforms.push_back(Platform(500, 225, 150, 25));
    level1_Platforms.push_back(Platform(1000, 325, 150, 25));
    level1_Platforms.push_back(Platform(2000, 250, 150, 25)); // Last Platform.
}

void LevelManager::Level1() {  
    //Load Environment  
    for(unsigned int i = 0; i < level1_Platforms.size(); i++) {
        if(i < 3) {
            level1_Platforms.at(i).Draw(GREEN);
        }
        else {
            level1_Platforms.at(i).Draw(RED);
        }
    }
}
void LevelManager::Level2() {
    //Starting Block
    DrawRectangle(0,320,500,1000,RED);

    //Main Platform
    DrawRectangle(0,320,10000,200,GREEN);

    //End Block
    DrawRectangle(10000,320,500,1000,RED);
}

void LevelManager::Level3() {
    DrawRectangle(0,320,15000,200,RED);
}

//Getters
vector<Platform> LevelManager::GetLevel1_Platforms() {
    return level1_Platforms;
}

vector<Platform> LevelManager::GetLevel2_Platforms() {
    return level2_Platforms;
}

vector<Platform> LevelManager::GetLevel3_Platforms() {
    return level3_Platforms;
}

vector<Enemy> LevelManager::GetLevel1_Enemies() {
    return level1_Enemy;
}

vector<Enemy> LevelManager::GetLevel2_Enemies() {
    return level2_Enemy;
}

vector<Enemy> LevelManager::GetLevel3_Enemies() {
    return level3_Enemy;
}
