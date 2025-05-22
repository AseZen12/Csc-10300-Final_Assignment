#include "platform.h"


Platform::Platform(float xPos, float yPos, float width, float height) {
    image =  {xPos, yPos, width , height};
    hitbox = {image.x, image.y, image.width, image.height};
}

int Platform::GetLocationX() {
    return image.x;
}
int Platform::GetLocationY() {
    return image.y;
}
void Platform::DrawHitBox(Color color) {
   DrawRectangleRec(hitbox, color);
}

Rectangle Platform::GetHitBox() {
    return hitbox;
}

void Platform::Draw(Color color) {
    DrawRectangleRec(image, color);
}