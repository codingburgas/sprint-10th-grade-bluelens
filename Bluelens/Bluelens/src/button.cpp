#include "../include/button.h"

bool IsButtonClicked(Button btn)
{
    Vector2 mousePos = GetMousePosition();
    bool hover = CheckCollisionPointRec(mousePos, btn.bounds);

    bool pressed = false;

    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !btn.clickedLastFrame)
    {
        pressed = true;
        btn.clickedLastFrame = true;
    }

    if (!IsMouseButtonDown(MOUSE_LEFT_BUTTON))
    {
        btn.clickedLastFrame = false;
    }

    return pressed;
}

void DrawButton(Button btn)
{
    Vector2 mousePos = GetMousePosition();
    bool hover = CheckCollisionPointRec(mousePos, btn.bounds);

    // Change color when hovered
    Color color = hover ? LIGHTGRAY : GRAY;

    DrawRectangleRec(btn.bounds, color);
    DrawRectangleLines(btn.bounds.x, btn.bounds.y, btn.bounds.width, btn.bounds.height, RAYWHITE);

    // Center text
    int textW = MeasureText(btn.text, btn.fontSize);
    int textX = btn.bounds.x + (btn.bounds.width - textW) / 2;
    int textY = btn.bounds.y + (btn.bounds.height - btn.fontSize) / 2;

    DrawText(btn.text, textX, textY, btn.fontSize, RAYWHITE);
}
