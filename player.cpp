#include "player.h"
#include <iostream>

//Constructor
Player::Player(int hearts, float x, float y) {
 health = hearts;
 xPosition = x;
 yPosition = y;
 LoadImages();
 hitBox =  {xPosition, yPosition, 160, 200};
 i = 0;
 
}

void Player::LoadImages() {
    //Left Facing
    playerImagesL.push_back(LoadTexture("./Assets_UnFoldable/IDLE_L.png"));
    playerImagesL.push_back(LoadTexture("./Assets_UnFoldable/STEP_One_L.png"));
    playerImagesL.push_back(LoadTexture("./Assets_UnFoldable/IDLE_L.png"));
    playerImagesL.push_back(LoadTexture("./Assets_UnFoldable/STEP_Two_L.png"));
    //Right Facing
    playerImagesR.push_back(LoadTexture("./Assets_UnFoldable/IDLE_R.png"));
    playerImagesR.push_back(LoadTexture("./Assets_UnFoldable/STEP_One_R.png"));
    playerImagesR.push_back(LoadTexture("./Assets_UnFoldable/IDLE_R.png"));
    playerImagesR.push_back(LoadTexture("./Assets_UnFoldable/STEP_Two_R.png"));
}

Rectangle Player::GetHitBox() {
    return hitBox;
}
//Draws the HitBox
void Player::DrawHitBox() {
    DrawRectangleRec(hitBox, RED);
}
//Draws the Image of the Player
void Player::Draw() {
    
    //DrawHitBox();
    if(IsKeyDown(KEY_LEFT)) {
        DrawTexture(playerImagesL.at(i++), xPosition, yPosition,WHITE);
    }
    else if(IsKeyDown(KEY_RIGHT)) {
        DrawTexture(playerImagesR.at(i++), xPosition, yPosition,WHITE);
    }
    else {
        DrawTexture(playerImagesR.at(0), xPosition, yPosition, WHITE);
    }
    if(i == 4) {
        i = 0;
    }
}

//Gets the Player's current number of hearts;
int Player::GetHealth() {
    return health;
}

//Updates the player's current number of hearts.
int Player::ChangeHealth(int hearts) {
    if(hearts < health && health > 0 && health < MAX_HEALTH) {
        health += hearts;
    }
    return -1;
}

int Player::GetX() {
    return xPosition;
}

int Player::GetY() {
    return yPosition;
}

void Player::SetX(int value) {
    xPosition = value;
}

void Player::SetY(int value) {
    yPosition = value;
}

void Player::ChangeX(int change) {
    xPosition += change;
}

void Player::ChangeY(int change) {
    yPosition += change;
}

void Player::SetX_Velocity(int velocity) {
    xVelocity = velocity;
}

void Player::SetY_Velocity(int velocity) {
    yVelocity = velocity;
}

int Player::GetX_Velocity() {
    return xVelocity;
}

int Player::GetY_Velocity() {
    return yVelocity;
}

void Player::Update() {
    //Updates Movement
    xPosition += xVelocity;
    yPosition += yVelocity;
    //Moves the visual Image
    //Moves HitBox
    hitBox.x = xPosition;
    hitBox.y = yPosition;

}

