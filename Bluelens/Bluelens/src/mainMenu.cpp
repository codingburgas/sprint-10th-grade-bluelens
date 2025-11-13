#include "../include/mainMenu.h"
#include "../include/howToPlay.h"

MenuState DrawMainMenu()
{
    DrawText("LABYRINTH GAME", GetScreenWidth() / 2 - 300, 100, 60, RAYWHITE);
    DrawText("1. Start Game", GetScreenWidth() / 2 - 200, 250, 40, RAYWHITE);
    DrawText("2. Controls", GetScreenWidth() / 2 - 200, 310, 40, RAYWHITE);
    DrawText("3. Exit", GetScreenWidth() / 2 - 200, 370, 40, RAYWHITE);
    DrawText("4. Themes", GetScreenWidth() / 2 - 200, 430, 40, RAYWHITE);

    if (IsKeyPressed(KEY_ONE)) return MENU_PLAYING;
    if (IsKeyPressed(KEY_TWO))
    {
        DrawControlsMenu();
        return MENU_CONTROLS;
    }
    if (IsKeyPressed(KEY_THREE))
    {
        CloseWindow();
    }
    if (IsKeyPressed(KEY_FOUR))
    {
    }

    return MENU_MAIN;
}

