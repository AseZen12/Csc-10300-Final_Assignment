#ifndef BUTTON_H
#define BUTTON_H

#include "raylib.h"

class Button {
private:
    Texture2D texture;
    Vector2 position;
    float width;
    float height;

public:
    Button(const char* imagePath, float x, float y);               // no scale
    Button(const char* imagePath, float x, float y, float scale);  // with scale
    ~Button();

    void Draw();
    bool IsClicked();
};

#endif
