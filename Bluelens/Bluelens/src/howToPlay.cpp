#include "../include/howToPlay.h"
#include "raylib.h"
#include <iostream>

void DrawControlsMenu()
{
    DrawText("CONTROLS:", 100, 100, 40, RAYWHITE);
    DrawText("WASD - Move", 100, 160, 30, RAYWHITE);
    DrawText("ESC - Pause", 100, 200, 30, RAYWHITE);
    DrawText("ENTER - Start Game", 100, 240, 30, RAYWHITE);
}

bool HandlePauseMenu(bool& gamePaused, bool& exitGame) {
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.6f));
    DrawText("PAUSED", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 150, 60, RAYWHITE);
    DrawText("1. Continue", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 - 50, 40, RAYWHITE);
    DrawText("2. Controls", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2, 40, RAYWHITE);
    DrawText("3. Exit", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 50, 40, RAYWHITE);

    if (IsKeyPressed(KEY_ONE)) gamePaused = false;
    if (IsKeyPressed(KEY_TWO)) DrawControlsMenu();
    if (IsKeyPressed(KEY_THREE)) exitGame = true;

    return exitGame;
}
