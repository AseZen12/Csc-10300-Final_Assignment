#ifndef SPEAKER_H
#define SPEAKER_H

#include "raylib.h"
#include <string>
using namespace std;

// this is for characters who talk — each one has a name and image
class Speaker {
private:
    string name;      // the character's name (like "You" or "Patch")
    Texture2D portrait;    // their image/face
    Vector2 position;      // where to draw them
    float scale;           // scale lets us shrink the picture (because it was too big)

public:
    // constructor to make a speaker — we give name, image path, position, and scale
    Speaker(const string name, const char* imagePath, Vector2 pos, float scale = 1.0f);
    ~Speaker();           // used to unload the image when done

    void Draw();          // draws the speaker's image
    string GetName(); // gives us the name
};

#endif
