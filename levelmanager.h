#include <iostream>
#include <vector>
#include "raylib.h"
#include "player.h"
#include "platform.h"
#include "prize.h"
#include "enemy.h"

using namespace std;


class LevelManager {
    public:
        LevelManager(int initlevel = 0, bool initState = 0);
        void UpdateLevel(int levelNumber, Player *insertedPlayer);
        void InitLevel();
        void Collision(vector<Platform> list,vector<Enemy> enemyList, Player* insertedPlayer);
        vector<Platform> GetLevel1_Platforms();
        vector<Platform> GetLevel2_Platforms();
        vector<Platform> GetLevel3_Platforms();
        vector<Enemy> GetLevel1_Enemies();
        vector<Enemy> GetLevel2_Enemies();
        vector<Enemy> GetLevel3_Enemies();
    private:
        int level;
        bool isActive;
        bool environmentCollision;
        bool enemyCollision;
        Prize  piece;
        vector<Platform> level1_Platforms;
        vector<Platform> level2_Platforms;
        vector<Platform> level3_Platforms;
        vector<Enemy> level1_Enemy;
        vector<Enemy> level2_Enemy;
        vector<Enemy> level3_Enemy;
        void Level1();
        void Level2();
        void Level3();

};