#include "../include/inputField.h"
#include <cctype>

void HandleInputField(InputField& field)
{
    // Click to activate/deactivate
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        field.active = CheckCollisionPointRec(mouse, field.bounds);
    }

    if (field.active)
    {
        // Get typed characters
        int key = GetCharPressed();
        while (key > 0)
        {
            // Only accept digits
            if (isdigit(key) && field.text.length() < 2)
            {
                field.text += (char)key;
            }
            key = GetCharPressed();
        }

        // Backspace to delete
        if (IsKeyPressed(KEY_BACKSPACE) && !field.text.empty())
        {
            field.text.pop_back();
        }
    }
}

void DrawInputField(InputField& field)
{
    // Draw box
    Color boxColor = field.active ? LIGHTGRAY : GRAY;
    DrawRectangleRec(field.bounds, boxColor);
    DrawRectangleLinesEx(field.bounds, 2, field.active ? BLUE : WHITE);

    // Draw text
    const char* display = field.text.empty() ? "" : field.text.c_str();
    DrawText(display, field.bounds.x + 10, field.bounds.y + 10, 30, BLACK);
}