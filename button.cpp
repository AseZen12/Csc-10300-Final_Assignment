#include "button.h"

// Normal (no scale)
Button::Button(const char* imagePath, float x, float y) {
    texture = LoadTexture(imagePath);
    position = { x, y };
    width = (float)texture.width;
    height = (float)texture.height;
}

// Scaled
Button::Button(const char* imagePath, float x, float y, float scale) {
    Image img = LoadImage(imagePath);
    int newWidth = (int)(img.width * scale);
    int newHeight = (int)(img.height * scale);
    ImageResize(&img, newWidth, newHeight);

    texture = LoadTextureFromImage(img);
    UnloadImage(img);

    position = { x, y };
    width = (float)newWidth;
    height = (float)newHeight;
}

Button::~Button() {
    UnloadTexture(texture);
}

void Button::Draw() {
    DrawTexture(texture, (int)position.x, (int)position.y, WHITE);
}

bool Button::IsClicked() {
    Vector2 mouse = GetMousePosition();
    Rectangle rect = { position.x, position.y, width, height };
    return CheckCollisionPointRec(mouse, rect) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}
