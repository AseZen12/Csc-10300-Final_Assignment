#include "enemy.h"

Enemy::Enemy(int xlocation, int ylocation) {
   xPosition = xlocation;
   yPosition = ylocation;
   hitBox = {xPosition, yPosition, 130, 40};
   LoadImages();
   i = 0; 
}

void Enemy::DrawHitBox() {
    DrawRectangleRec(hitBox, RED);
}

void Enemy::Draw() {
    DrawHitBox();
    if(xVelocity < 0) {
        DrawTexture(enemyImagesL.at(i++), xPosition, yPosition,WHITE);
    }
    else if(xVelocity > 0) {
        DrawTexture(enemyImagesR.at(i++), xPosition, yPosition,WHITE);
    }
    else {
        DrawTexture(enemyImagesR.at(0), xPosition, yPosition, WHITE);
    }
    if (i == 4) {
        i = 0;
    }
}

void Enemy::LoadImages() {
    //Left Facing
    enemyImagesR.push_back(LoadTexture("./Assets_UnFoldable/Enemy_IDLE_R.png"));
    enemyImagesR.push_back(LoadTexture("./Assets_UnFoldable/Enemy_STEP_One_R.png"));
    enemyImagesR.push_back(LoadTexture("./Assets_UnFoldable/Enemy_IDLE_R.png"));
    enemyImagesR.push_back(LoadTexture("./Assets_UnFoldable/Enemy_STEP_Two_R.png"));
    //Right Facing
    enemyImagesL.push_back(LoadTexture("./Assets_UnFoldable/Enemy_IDLE_L.png"));
    enemyImagesL.push_back(LoadTexture("./Assets_UnFoldable/Enemy_STEP_One_L.png"));
    enemyImagesL.push_back(LoadTexture("./Assets_UnFoldable/Enemy_IDLE_L.png"));
    enemyImagesL.push_back(LoadTexture("./Assets_UnFoldable/Enemy_STEP_Two_L.png"));
}