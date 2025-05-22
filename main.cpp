#include "raylib.h"
#include "button.h"
#include "dialogue.h"
#include "speaker.h"
#include "levelmanager.h"


/*

Team member: Tanveer Hassan Khan + Bradley Roberts
Resources used: ChatGPT (for image generation: you.png, patch.png, play.png, exit.png
Main Character and Asset design: Bradley
Movement Implementation: Bradley
UI Implementation: Tanveer
Background theme and Buttons generation: Tanveer

Learned the Library using: https://www.raylib.com/cheatsheet/cheatsheet.html and  https://www.youtube.com/watch?v=RGzj-PF7D74&list=PLwR6ZGPvjVOTIMqUXnqyWaIfQg0xdHNZn

Games Description:

*/

int main() {
    // create the game window — standard 1280x720
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Unfoldable - Cardboard RPG");
    SetTargetFPS(60);  // keeps game running smooth — 60 is common default

    // backgrounds (menu and story and ending)
    Texture2D menuBG = LoadTexture("background.png"); // for menu screen
    Texture2D introBG = LoadTexture("introBG.png"); // for story/dialogue screen
    Texture2D labBG = LoadTexture("lab.png"); // when working on gun
    Texture2D gunDoneBG = LoadTexture("gundone.png"); // when the gun is done making
    Texture2D exitBG = LoadTexture("exitbg.png"); // waving at the box

    // buttons for menu screen
    Button play("play.png", 512, 250); // play button in middle-ish
    Button exit("exit.png", 520, 420, 0.925f); // exit button below it, scaled a bit

    // End Stage button (placed lower center)
    Button endStageBtn("end.png", 512, 480, 0.9f); // adjust position and scale as needed

    // Popup buttons (Yes/No)
    Button yesBtn("yes.png", 380, 300, 0.7f); // reusing existing button images
    Button noBtn("no.png", 720, 300, 0.7f); // adjust for spacing


    // screen state variable — lets us switch between menu and dialogue
    const int SCREEN_MENU = 0;
    const int SCREEN_DIALOGUE = 1;
    const int SCREEN_LEVEL_MENU = 2;
    const int SCREEN_LAB = 3;
    const int SCREEN_GUN_DONE = 4;
    const int SCREEN_EXIT = 5;
    const int SCREEN_LEVEL = 6;

    int currentScreen = SCREEN_MENU; // start on the menu

    // ----------------------------------------
    // FIXING PORTRAIT SIZE AND POSITION BELOW
    // ----------------------------------------

    // our images (you.png and patch.png) are 1024x1024 which is HUGE
    float portraitScale = 0.4f; // 1024 → 256 pixels

    // calculate new size manually using basic math
    int scaledWidth = (int)(1024 * portraitScale);  // becomes 256
    int scaledHeight = (int)(1024 * portraitScale); // also 256

    // vertically center the portraits
    int centerY = (720 - scaledHeight) / 2 - 15; // 720 is screen height

    // YOU goes on the left side (80 px padding from edge)
    Speaker you("You", "you.png", { 80.0f, (float)centerY }, portraitScale);

    // PATCH goes on the right side
    // we do: screen width - portrait width - 80px padding
    float patchX = 1280 - scaledWidth - 80;
    Speaker patch("Patch", "patch.png", { patchX, (float)centerY }, portraitScale);

    // narrator has no image, just a blank png to avoid crashing (we fake it)
    Speaker narrator(" ", "blank.png", { 0, 0 }, 1.0f);

    // dialogue manager — handles our story
    DialogueManager dm;

    //Level Information
    Player player(3, 0, 100);
    LevelManager levels(0, false);
    levels.InitLevel();
   
    //Player Camera
    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.GetX() + 20.0f, player.GetY() + 20.0f };
    camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 0.5f;

    // ----------------------------------------
    // INTRO NARRATIVE (the cardboard backstory)
    // ----------------------------------------

    dm.AddLine(&narrator, "You were a broke college student....");
    dm.AddLine(&narrator, "One day, you ran into a salesperson giving out flyers for survey.");
    dm.AddLine(&narrator, "*GET 200$ FOR TAKING THE SURVEY,* it said.");
    dm.AddLine(&narrator, "Desperation hits.");
    dm.AddLine(&narrator, "You decide to take the survey and carry on with the experiment....");

    // ----------------------------------------
    // CONVERSATION STARTS HERE
    // ----------------------------------------

    dm.AddLine(&you, "Where...am...I...?");
    dm.AddLine(&patch, "Thank goodness you are awake!");
    dm.AddLine(&patch, "We found you near the edge of the box.");
    dm.AddLine(&you, "The box?");
    dm.AddLine(&patch, "It is the Surveyors work again.");
    dm.AddLine(&patch, "Rebuild the ray gun. It is your only way out.");
    dm.AddLine(&you, "What do I need?");
    dm.AddLine(&patch, "Power cell. Lens. Frame. Bring them back.");

    // NOTE: doesn't do anything special after the last line — maybe add that later

    /**
    ----------------------------------------
    LEVEL_MENU - Variables;
    ----------------------------------------
    **/

    //MENU_Buttons:

    Button level1("./Assets_UnFoldable/Stage_Two_Icon.png", 512, 250, 0.25f);
    Button level2("./Assets_UnFoldable/Stage_One_Icon.png",256, 250,0.25f);
    Button level3("./Assets_UnFoldable/Stage_Three_Icon.png", 768, 250, 0.25f);

    bool showPopup = false; // should we show the "Have you played?" popup
    bool enterPressedNarrative = false;

    while (!WindowShouldClose()) {
        // --------------------------------
        // Input & State Updates (Game Logic)
        // --------------------------------
        if (currentScreen == SCREEN_MENU) {
            if (play.IsClicked()) currentScreen = SCREEN_DIALOGUE;
            if (exit.IsClicked()) CloseWindow();
        }
        else if (currentScreen == SCREEN_DIALOGUE) {
            dm.Update();
        }

        // auto-transition to level menu after dialogue
        if (dm.IsFinished() && currentScreen == SCREEN_DIALOGUE) {
            currentScreen = SCREEN_LEVEL_MENU;
        }
        //Gravity
       if(player.GetY() <= 500) {
            player.SetY_Velocity(100);
       } 

     //Player Controls
       //Movement
       if(IsKeyDown(KEY_LEFT)) {
            player.SetX_Velocity(-25);
       }
       else if(IsKeyDown(KEY_RIGHT)) {
          player.SetX_Velocity(25);
       }
       else {
          player.SetX_Velocity(0);
       }
       //Jumping
       if (IsKeyPressed(KEY_SPACE)) {
          player.SetY_Velocity(-250);
       }
       //Camera following player
       camera.target = (Vector2){player.GetX() + 20, player.GetY() + 20};
        // --------------------------------
        // Drawing Section
        // --------------------------------
        BeginDrawing();
        ClearBackground(BLACK);

        // --------------------
        // MAIN MENU SCREEN
        // --------------------
        if (currentScreen == SCREEN_MENU) {
            DrawTexture(menuBG, 0, 0, WHITE);
            play.Draw();
            exit.Draw();
        }

        // --------------------
        // DIALOGUE SCREEN
        // --------------------
        else if (currentScreen == SCREEN_DIALOGUE) {
            DrawTexture(introBG, 0, 0, WHITE);
            dm.Draw();
        }

        // --------------------
        // LEVEL MENU SCREEN
        // --------------------
        else if (currentScreen == SCREEN_LEVEL_MENU) {
            DrawTexture(introBG, 0, 0, WHITE);
            level1.Draw();
            level2.Draw();
            level3.Draw();
            endStageBtn.Draw();

            if(level1.IsClicked()) {
                currentScreen = SCREEN_LEVEL;
            }


            if (endStageBtn.IsClicked()) showPopup = true;

            if (showPopup) {
                // popup background
                DrawRectangle(300, 200, 680, 300, Fade(BLACK, 0.8f));
                DrawRectangleLines(300, 200, 680, 300, WHITE);
                DrawText("Have you played all 3 stages?", 460, 280, 24, RAYWHITE);
                yesBtn.Draw();
                noBtn.Draw();

                if (yesBtn.IsClicked()) {
                    currentScreen = SCREEN_LAB;
                    showPopup = false;
                }

                if (noBtn.IsClicked()) {
                    showPopup = false;
                }
            }
        }
        // LEVEL State
        if(currentScreen == SCREEN_LEVEL){
                SetTargetFPS(15);
                BeginMode2D(camera); 
                    player.Update(); 
                    levels.UpdateLevel(1, &player);
                    player.Draw();
                    DrawLine(-500,500,5000,500,BLACK);
                EndMode2D();
        }

        // --------------------
        // LAB SCREEN
        // --------------------
        else if (currentScreen == SCREEN_LAB) {
            DrawTexture(labBG, 0, 0, WHITE);
            DrawRectangle(100, 550, 1080, 150, Fade(BLACK, 0.7f));
            DrawRectangleLines(100, 550, 1080, 150, WHITE);
            DrawText("After I bought all the parts, me and Patch went to the lab and started working on it", 120, 610, 24, WHITE);
            DrawText("[Press ENTER to continue]", 500, 670, 20, GRAY);

            if (IsKeyPressed(KEY_ENTER) && !enterPressedNarrative) {
                currentScreen = SCREEN_GUN_DONE;
                enterPressedNarrative = true;
            }
            if (IsKeyReleased(KEY_ENTER)) {
                enterPressedNarrative = false;
            }
        }

        // --------------------
        // GUN COMPLETED SCREEN
        // --------------------
        else if (currentScreen == SCREEN_GUN_DONE) {
            DrawTexture(gunDoneBG, 0, 0, WHITE);
            DrawRectangle(100, 550, 1080, 150, Fade(BLACK, 0.7f));
            DrawRectangleLines(100, 550, 1080, 150, WHITE);
            DrawText("After countless hours of tinkering, we have finally made the gun to work.", 120, 585, 24, WHITE);
            DrawText("It is also sad to see that my time has to come an end with my new friends.", 120, 610, 24, WHITE);
            DrawText("But all good must come to an end, and so I let Patch use the gun on me", 120, 635, 24, WHITE);
            DrawText("[Press ENTER to continue]", 500, 670, 20, GRAY);

            if (IsKeyPressed(KEY_ENTER) && !enterPressedNarrative) {
                currentScreen = SCREEN_EXIT;
                enterPressedNarrative = true;
            }
            if (IsKeyReleased(KEY_ENTER)) {
                enterPressedNarrative = false;
            }
        }

        // --------------------
        // FINAL EXIT SCENE
        // --------------------
        else if (currentScreen == SCREEN_EXIT) {
            DrawTexture(exitBG, 0, 0, WHITE);
            DrawRectangle(100, 550, 1080, 150, Fade(BLACK, 0.7f));
            DrawRectangleLines(100, 550, 1080, 150, WHITE);
            DrawText("After that experience, I will always think twice before accepting a random offer.", 120, 610, 24, WHITE);
            DrawText("But, thanks for coming with me anyways!", 120, 635, 24, WHITE);
        }

        EndDrawing();
    }

    // ----------------------------
    // cleanup section
    // ----------------------------

    CloseWindow(); // closes game window

    return 0;
}
