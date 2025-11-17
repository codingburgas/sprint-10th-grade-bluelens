#pragma once
#include "raylib.h"

// Represents a simple UI button.
struct Button {
    Rectangle bounds;
    const char* text;
    int fontSize;
};

// Checks whether the button has been clicked.
bool IsButtonClicked(Button btn);
// Draws the button on the screen.
void DrawButton(Button btn);