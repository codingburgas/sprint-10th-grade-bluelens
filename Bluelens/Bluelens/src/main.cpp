#include "raylib.h"
#include "../include/maze.h"
#include "../include/mainMenu.h"
#include "../include/howToPlay.h"
#include "../include/theme.h"
#include "../include/inputField.h"
#include <vector>
#include <ctime> 

int main()
{
    InitWindow(800, 800, "Labyrinth Game");
    SetTargetFPS(60);
    srand(time(0));

    MenuState menuState = MENU_MAIN;
    bool gamePaused = false;
    bool exitGame = false;
    int levelCleared = 0;
    int mazeSize = 20, customSize = 20;
    const int cellSize = 30;

    std::vector<std::vector<Cell>> maze;
    Player player{ 0, 0 };
    std::vector<Enemy> enemies;

    GenerateMaze(maze, mazeSize, mazeSize);

    while (!WindowShouldClose())
    {
        Theme currentTheme = GetCurrentTheme();
        BeginDrawing();
        ClearBackground(currentTheme.background);

        switch (menuState)
        {
        case MENU_MAIN:
            menuState = DrawMainMenu();
            if (menuState == MENU_PLAYING)
            {
                levelCleared = 0;
                mazeSize = 20;
                GenerateMaze(maze, mazeSize, mazeSize);
                player = { 0, 0 };
                gamePaused = false;
            }
            if (menuState == MENU_EXIT)
            {
                EndDrawing();
                CloseWindow();
                return 0;
            }
            break;

        case MENU_THEMES:
            menuState = DrawThemesMenu();
            break;

        case MENU_CONTROLS:
            menuState = DrawControlsMenu();
            break;

        case MENU_PLAYING:
        {  
            bool mazeFinished = false;
            MovePlayer(player, maze, levelCleared, mazeFinished);
            DrawMaze(maze, cellSize, player, enemies);
            DrawText(TextFormat("Level: %i", levelCleared + 1), GetScreenWidth() - 150, 10, 30, currentTheme.textColor);

            if (mazeFinished)
            {
                GenerateMaze(maze, mazeSize, mazeSize);
                player = { 0, 0 };
            }
        }
        break;

        case MENU_CUSTOM:
            menuState = DrawCustomMenu(customSize);
            if (menuState == MENU_PLAYING)
            {
                levelCleared = 0;
                mazeSize = customSize;
                GenerateMaze(maze, mazeSize, mazeSize);
                player = { 0, 0 };
                gamePaused = false;
            }
            break;

        case MENU_EXIT:
            EndDrawing();
            CloseWindow();
            return 0;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0; 
}