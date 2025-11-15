#include "../include/mainMenu.h"
#include "../include/howToPlay.h"
#include "../include/maze.h"
#include "../include/button.h"
#include "raylib.h"



MenuState DrawMainMenu()
{
    //Button definition
    Button btnStart = { { GetScreenWidth() / 2 - 150, 250, 300, 60 }, "Start Game", 30 };
    Button btnControls = { { GetScreenWidth() / 2 - 150, 330, 300, 60 }, "Controls",   30 };
    Button btnThemes = { { GetScreenWidth() / 2 - 150, 410, 300, 60 }, "Themes",     30 };
    Button btnExit = { { GetScreenWidth() / 2 - 150, 490, 300, 60 }, "Exit Game",  30 };

    DrawText("LABYRINTH GAME", GetScreenWidth() / 2 - 300, 100, 60, RAYWHITE);

    // Draw buttons
    DrawButton(btnStart);
    DrawButton(btnControls);
    DrawButton(btnExit);
    DrawButton(btnThemes);

    if (IsButtonClicked(btnStart))    return MENU_PLAYING;
    if (IsButtonClicked(btnControls)) return MENU_CONTROLS;
    if (IsButtonClicked(btnExit))     return MENU_EXIT;
    if (IsButtonClicked(btnThemes)) return MENU_MAIN;

    return MENU_MAIN;
}

