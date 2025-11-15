#include "../include/howToPlay.h"
#include "../include/button.h"
#include "../include/mainMenu.h"
#include "raylib.h"
#include <iostream>

MenuState DrawControlsMenu()
{
    Button btnReturnToMainM = { { GetScreenWidth() / 2 - 150, 300, 350, 60 },"Return to Main Menu", 30 };
    DrawText("CONTROLS:", 100, 100, 40, RAYWHITE);
    DrawText("WASD - Move", 100, 160, 30, RAYWHITE);
    DrawText("ESC - Pause", 100, 200, 30, RAYWHITE);
    DrawText("YOUR GOAL IS TO REACH THE BOTTOM RIGHT CORNER", 100, 240, 24, RAYWHITE);
    DrawButton(btnReturnToMainM);
    if (IsButtonClicked(btnReturnToMainM))
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
