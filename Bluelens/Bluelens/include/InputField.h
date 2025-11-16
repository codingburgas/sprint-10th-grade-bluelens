#pragma once
#include "raylib.h"
#include <string>

struct InputField
{
    Rectangle bounds;
    std::string text;
    bool active;
};

void HandleInputField(InputField& field);
void DrawInputField(InputField& field);