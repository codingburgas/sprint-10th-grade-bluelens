#include "raylib.h"
#include "../maze.h"
#include "../mainMenu.h"
#include "../howToPlay.h"
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

    const int width = 20, height = 20, cellSize = 30;
    std::vector<std::vector<Cell>> maze;
    Player player{ 0,0 };
    std::vector<Enemy> enemies;

    GenerateMaze(maze, width, height);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKGRAY);

        switch (menuState)
        {
        case MENU_MAIN:
            menuState = DrawMainMenu();
            break;
        case MENU_CONTROLS:
            DrawControlsMenu();
            if (IsKeyPressed(KEY_BACKSPACE)) menuState = MENU_MAIN;
            break;
        case MENU_PLAYING:
            if (IsKeyPressed(KEY_ESCAPE))
                gamePaused = !gamePaused;

            if (!gamePaused)
            {
                bool mazeFinished = false;
                MovePlayer(player, maze, levelCleared, mazeFinished);
                DrawMaze(maze, cellSize, player, enemies);
                DrawText(TextFormat("Level: %i", levelCleared + 1), 10, 10, 30, RAYWHITE);

                if (mazeFinished)
                {
                    GenerateMaze(maze, width, height);
                    player = { 0,0 };
                }
            }
            else
            {
                if (HandlePauseMenu(gamePaused, exitGame) || exitGame) CloseWindow();
            }
            break;
        }

        EndDrawing();
    }

    CloseWindow();
}

