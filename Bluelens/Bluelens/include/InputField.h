#pragma once
#include "raylib.h"
#include <string>

// Represents a text input field that the user can type into.
struct InputField
{
    Rectangle bounds;
    std::string text;
    bool active;
};

void HandleInputField(InputField& field);
void DrawInputField(InputField& field);