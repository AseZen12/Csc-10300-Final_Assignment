#include "dialogue.h"
using namespace std;

// setup values
DialogueManager::DialogueManager() {
    currentLine = 0;      // we start from the first line
    enterPressed = false; // helps us make sure we don't spam Enter
}

// adds a new line to the convo
void DialogueManager::AddLine(Speaker* speaker, const string text) {
    lines.push_back({ speaker, text }); // push line to end of list
}

// this updates the logic
// we use IsKeyPressed from raylib to move to the next line
void DialogueManager::Update() {
    if (IsKeyPressed(KEY_ENTER) && !enterPressed) {
        currentLine++;     // move to next line
        enterPressed = true;
    }

    if (IsKeyReleased(KEY_ENTER)) {
        enterPressed = false; // reset so we can press again
    }

    // NOTE: no check for currentLine going out of bounds, so it might go too far
}

// this draws everything: character, textbox, name, dialogue
void DialogueManager::Draw() {
    if (currentLine >= lines.size()) return;  // do nothing if all done

    DialogueLine line = lines[currentLine];   // get the line we're on

    // draw the speakers portrait (they're left or right)
    line.speaker->Draw(); // uses speaker's draw method

    // draw the textbox at the bottom
    DrawRectangle(100, 550, 1080, 150, Fade(BLACK, 0.7f));   // semi-transparent box
    DrawRectangleLines(100, 550, 1080, 150, WHITE);          // white border

    // draw the speaker's name at the top of the box
    DrawText(line.speaker->GetName().c_str(), 120, 560, 24, ORANGE);  // orange for names

    // draw the actual dialogue text (centered)
    int fontSize = 24;
    int textWidth = MeasureText(line.text.c_str(), fontSize);  // measure size of text
    int textX = (1280 - textWidth) / 2;                         // center it (hardcoded width)
    DrawText(line.text.c_str(), textX, 610, fontSize, WHITE);  // draw the dialogue
    // raylib functions like DrawText() expect a const char*, not an string, which is why c_str is used to convert.
    // this method was improvised from the concept given here: https://stackoverflow.com/questions/15502541/convert-c-string-to-char-array

    // draw the [ENTER] help text
    const char* helpText = "[Press ENTER to continue]";
    int helpSize = 20;
    int helpWidth = MeasureText(helpText, helpSize);
    int helpX = (1280 - helpWidth) / 2;
    DrawText(helpText, helpX, 670, helpSize, GRAY);  // this one in gray
}

// lets us check if we're done with all lines (but I didnt use it in main.cpp yet)
bool DialogueManager::IsFinished() {
    return currentLine >= lines.size();  // true when done
}

