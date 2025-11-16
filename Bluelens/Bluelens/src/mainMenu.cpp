#include "../include/mainMenu.h"
#include "../include/howToPlay.h"
#include "../include/maze.h"
#include "../include/button.h"
#include "../include/theme.h"
#include "../include/InputField.h"
#include <string>
#include "raylib.h"



MenuState DrawMainMenu()
{
    Theme currentTheme = GetCurrentTheme();
    int startY = 200;
    int buttonHeight = 60;
    int spacing = 20;

        //Button definition
    Button btnStart = { {GetScreenWidth() / 2 - 150, (startY + 0 * (buttonHeight + spacing)), 300, buttonHeight }, "Start", 30 };
    Button btnCustom = { {GetScreenWidth() / 2 - 150, (startY + 1 * (buttonHeight + spacing)), 300, buttonHeight }, "Custom", 30 };
    Button btnControls = { {GetScreenWidth() / 2 - 150, (startY + 2 * (buttonHeight + spacing)), 300, buttonHeight }, "Controls", 30 };
    Button btnThemes = { {GetScreenWidth() / 2 - 150, (startY + 3 * (buttonHeight + spacing)), 300, buttonHeight }, "Themes", 30 };
    Button btnExit = { {GetScreenWidth() / 2 - 150, (startY + 4 * (buttonHeight + spacing)), 300, buttonHeight }, "Exit Game", 30 };

        DrawText("LABYRINTH GAME", GetScreenWidth() / 2 - 300, 100, 60, currentTheme.textColor);

        // Draw buttons
        DrawButton(btnStart);
        DrawButton(btnCustom);
        DrawButton(btnControls);
        DrawButton(btnExit);
        DrawButton(btnThemes);

        if (IsButtonClicked(btnStart))    return MENU_PLAYING;
        if (IsButtonClicked(btnControls)) return MENU_CONTROLS;
        if (IsButtonClicked(btnExit))     return MENU_EXIT;
        if (IsButtonClicked(btnThemes)) return MENU_THEMES;
        if (IsButtonClicked(btnCustom)) return MENU_CUSTOM;

        return MENU_MAIN;
}
MenuState DrawThemesMenu()
{
    Theme currentTheme = GetCurrentTheme();
    DrawText("SELECT THEME", GetScreenWidth() / 2 - 200, 80, 50, currentTheme.textColor);

    int startY = 180;
    int buttonHeight = 60;
    int spacing = 20;

    //Theme button output
    for (int i = 0; i < THEME_COUNT; i++)
    {
        Button themeBtn = {
            { GetScreenWidth() / 2 - 200, (float)(startY + i * (buttonHeight + spacing)), 400, (float)buttonHeight },
            themes[i].name,
            30
        };

        if (i == currentThemeIndex)
        {
            DrawRectangleRec(themeBtn.bounds, currentTheme.playerColor);
            DrawRectangleLines(themeBtn.bounds.x, themeBtn.bounds.y,
                themeBtn.bounds.width, themeBtn.bounds.height,
                currentTheme.textColor);

            int textW = MeasureText(themeBtn.text, themeBtn.fontSize);
            int textX = themeBtn.bounds.x + (themeBtn.bounds.width - textW) / 2;
            int textY = themeBtn.bounds.y + (themeBtn.bounds.height - themeBtn.fontSize) / 2;
            DrawText(themeBtn.text, textX, textY, themeBtn.fontSize, currentTheme.textColor);
        }
        else
        {
            DrawButton(themeBtn);
        }
        if (IsButtonClicked(themeBtn))
        {
            SetTheme(i);
        }
    }
    Button btnReturnToMainM = {{ GetScreenWidth() / 2 - 150, (float)(startY + THEME_COUNT * (buttonHeight + spacing) + 40), 340, 80 },"Return to Main Menu",30};
    DrawButton(btnReturnToMainM);

    if (IsButtonClicked(btnReturnToMainM))
    {
        return MENU_MAIN;
    }

    return MENU_THEMES;
}
MenuState DrawCustomMenu(int& mazeSize)
{
    Theme currentTheme = GetCurrentTheme();
    DrawText("CUSTOM GAME", 230, 100, 50, currentTheme.textColor);

    static std::string input = "";
    static bool initialized = false;
    static bool active = false;

    // Initialize input once
    if (!initialized)
    {
        input = std::to_string(mazeSize);
        initialized = true;
    }

    Rectangle box = { 300, 250, 200, 60 };

    DrawText("Maze Size:", 320, 200, 30, currentTheme.textColor);
    DrawText("(10-50)", 360, 330, 20, currentTheme.textColor);

    // Handle clicking on the box
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        Vector2 mouse = GetMousePosition();
        active = CheckCollisionPointRec(mouse, box);
    }

    // Handle text input when active
    if (active)
    {
        int key = GetCharPressed();
        while (key > 0)
        {
            if (key >= '0' && key <= '9' && input.length() < 2)
            {
                input += (char)key;
            }
            key = GetCharPressed();
        }

        // Handle backspace
        if (IsKeyPressed(KEY_BACKSPACE) && !input.empty())
        {
            input.pop_back();
        }
    }

    DrawRectangleRec(box, active ? currentTheme.buttonHoverColor : currentTheme.buttonColor);
    DrawRectangleLinesEx(box, 2, active ? currentTheme.buttonColor : currentTheme.textColor);

    const char* displayText = input.empty() ? " " : input.c_str();
    DrawText(displayText, box.x + 80, box.y + 15, 30, currentTheme.textColor);

    if (active && ((int)(GetTime() * 2) % 2 == 0))
    {
        int textWidth = MeasureText(displayText, 30);
        DrawLine(box.x + 80 + textWidth + 5, box.y + 15,
            box.x + 80 + textWidth + 5, box.y + 45, currentTheme.textColor);
    }

    Button btnStart = { {275, 400, 250, 60}, "Start Game", 30 };
    Button btnBack = { {240, 480, 330, 60}, "Return To Main Menu", 28 };
    DrawButton(btnStart);
    DrawButton(btnBack);

    if (IsButtonClicked(btnStart))
    {
        int val = input.empty() ? 20 : std::stoi(input);
        if (val < 10) val = 10;
        if (val > 50) val = 50;
        mazeSize = val;
        input = std::to_string(val);
        initialized = false; 
        return MENU_PLAYING;
    }

    if (IsButtonClicked(btnBack))
    {
        initialized = false; 
        return MENU_MAIN;
    }

    return MENU_CUSTOM;
}

