#ifndef DIALOGUE_H
#define DIALOGUE_H

#include "raylib.h"     // for drawing things like rectangles and text
#include "speaker.h"    // we use Speaker* to know who's talking
#include <vector>       // to store a list of lines
#include <string>       // for using regular text
using namespace std;

// this is one line of dialogue, has a speaker and what they say
struct DialogueLine {
    Speaker* speaker;        // who is saying the line
    string text;        // what the line says
};

// this class controls the whole convo
// I made a class so we can reuse this for other cutscenes later
class DialogueManager {
private:
    vector<DialogueLine> lines;  // all lines in order
    int currentLine;                  // which line we're currently showing
    bool enterPressed;                // so holding Enter doesn’t skip multiple lines

public:
    DialogueManager();   // constructor
    void AddLine(Speaker* speaker, const string text); // add new line to convo
    void Update();       // move to next line if needed
    void Draw();         // draw text, box, and speaker portrait
    bool IsFinished();   // checks if all lines are done (but I kinda didn’t use it)
};

#endif

