#include "../include/button.h"
#include "../include/theme.h"

bool IsButtonClicked(Button btn)
{
    Vector2 mousePos = GetMousePosition();
    bool hover = CheckCollisionPointRec(mousePos, btn.bounds);

    if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        return true;

    return false;
}

void DrawButton(Button btn)
{
    Theme currentTheme = GetCurrentTheme();
    Vector2 mousePos = GetMousePosition();
    bool hover = CheckCollisionPointRec(mousePos, btn.bounds);

    // Use theme colors
    Color color = hover ? currentTheme.buttonHoverColor : currentTheme.buttonColor;

    DrawRectangleRec(btn.bounds, color);
    DrawRectangleLines(btn.bounds.x, btn.bounds.y, btn.bounds.width, btn.bounds.height, currentTheme.textColor);

    // Center text
    int textW = MeasureText(btn.text, btn.fontSize);
    int textX = btn.bounds.x + (btn.bounds.width - textW) / 2;
    int textY = btn.bounds.y + (btn.bounds.height - btn.fontSize) / 2;

    DrawText(btn.text, textX, textY, btn.fontSize, currentTheme.textColor);
}