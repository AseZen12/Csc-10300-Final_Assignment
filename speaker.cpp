#include "speaker.h"
using namespace std;

// when we make a new speaker, we save their name, load image, position, and scale
Speaker::Speaker(const string name, const char* imagePath, Vector2 pos, float scale) {
    this->name = name;
    this->portrait = LoadTexture(imagePath); // loads image using raylib
    this->position = pos;
    this->scale = scale; // lets us shrink image if it’s too big
}

// when speaker is destroyed, we clean up their image
Speaker::~Speaker() {
    UnloadTexture(portrait); // raylib function to clean memory
}

// draws the image using raylib’s DrawTextureEx so we can scale it down
void Speaker::Draw() {
    DrawTextureEx(portrait, position, 0.0f, scale, WHITE); // found on raylib cheatsheet
}

// gives us the speaker’s name
string Speaker::GetName() {
    return name;
}
