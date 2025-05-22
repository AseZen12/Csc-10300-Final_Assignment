#include "raylib.h"

class Prize {
    public:
    Rectangle GetHitBox();
    bool GetIsCollected();

    private:
    Texture2D image;
    Rectangle hitBox;
    bool isCollected;

};