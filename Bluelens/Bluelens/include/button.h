#pragma once
#include "raylib.h"

struct Button 
{
    Rectangle bounds;
    const char* text;
    int fontSize;
    bool clickedLastFrame = false;
};

bool IsButtonClicked(Button btn);
void DrawButton(Button btn);