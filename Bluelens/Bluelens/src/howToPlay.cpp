#include "../include/howToPlay.h"
#include "../include/button.h"
#include "../include/mainMenu.h"
#include "../include/theme.h"
#include "raylib.h"
#include <iostream>

MenuState DrawControlsMenu()
{
    Theme currentTheme = GetCurrentTheme();
    Button btnReturnToMainM = { { GetScreenWidth() / 2 - 150, 300, 350, 60 },"Return to Main Menu", 30};
    DrawText("CONTROLS:", 100, 100, 40,  currentTheme.textColor);
    DrawText("WASD - Move", 100, 160, 30,  currentTheme.textColor);
    DrawText("ESC - Pause", 100, 200, 30 , currentTheme.textColor);
    DrawText("YOUR GOAL IS TO REACH THE BOTTOM RIGHT CORNER", 100, 240, 24, currentTheme.textColor);
    DrawButton(btnReturnToMainM);
    if(IsButtonClicked(btnReturnToMainM))
    {
        return MENU_MAIN;
    }
    return MENU_CONTROLS;
}

bool HandlePauseMenu(bool& gamePaused, bool& exitGame) {

    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.6f));
    DrawText("PAUSED", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 150, 60, RAYWHITE);
    DrawText("1. Continue", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 50, 40, RAYWHITE);
    DrawText("2. Controls", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2, 40, RAYWHITE);
    DrawText("3. Exit", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 50, 40, RAYWHITE);
    DrawText("4. Themes", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 100, 40, RAYWHITE);

    return exitGame;
}
