#include "raylib.h"

class Platform {
    public:
    Platform(float xPos, float yPos, float width, float height);
    void Draw(Color color);
    void DrawHitBox(Color color);
    Rectangle GetHitBox();
    int GetLocationX();
    int GetLocationY();


    private:
    Rectangle image; //The Visual Representation
    Rectangle hitbox;// The Collision Space.
};