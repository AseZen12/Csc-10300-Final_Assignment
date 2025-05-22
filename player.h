#include <raylib.h>
#include <iostream>
#include <vector>

using namespace std;

class Player {
    public:
    Player(int hearts = 3, float x = 0.0 , float y = 0.0);
    int GetHealth();
    int ChangeHealth(int hearts);
    int GetX();
    int GetY();
    void SetX(int value);
    void SetY(int value);
    void ChangeX(int change);
    void ChangeY(int change);
    void SetX_Velocity(int velocity);
    void SetY_Velocity(int velocity);
    int GetX_Velocity();
    int GetY_Velocity();
    void Draw();
    void DrawHitBox();
    void Update();
    Rectangle GetHitBox();
    //void Update();

    private:
    float xPosition;
    float yPosition; 
    int xVelocity;
    int yVelocity;
    int health; //Number Of Hearts
    vector<Texture2D> playerImagesL; // Left Facing
    vector<Texture2D> playerImagesR; //Right Facing
    Rectangle hitBox; //Player HitBox
    const int MAX_HEALTH = 100;
    void LoadImages();
    int i; //Animation counting variable
};
