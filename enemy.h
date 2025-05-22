#include "raylib.h"
#include "vector"

using namespace std;

class Enemy {
    public:
    Enemy(int xlocation, int ylocation);
    Rectangle GetHitBox();
    int GetX();
    int GetY();
    int GetX_Velocity();
    int GetY_Velocity();
    void Draw();
    void DrawHitBox();
    
    private:
    vector<Texture2D> enemyImagesR;
    vector<Texture2D> enemyImagesL;
    Rectangle hitBox;
    float xPosition;
    float yPosition;
    int xVelocity;
    int yVelocity;
    void LoadImages();
    int i;
};