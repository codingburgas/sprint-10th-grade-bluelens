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
    int lives = 3;
    int mazeSize = 20, customSize = 20;
    const int cellSize = 30;

    std::vector<std::vector<Cell>> maze;
    Player player{ 0, 0 };
    std::vector<Enemy> enemies;

    float enemyMoveTimer = 0.0f;

    GenerateMaze(maze, mazeSize, mazeSize);
    SpawnEnemies(enemies, maze, player, levelCleared + 1);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();
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
                lives = 3;
                mazeSize = 20;
                GenerateMaze(maze, mazeSize, mazeSize);
                player = { 0, 0 };
                gamePaused = false;
                SpawnEnemies(enemies, maze, player, levelCleared + 1);
            }
            if (menuState == MENU_EXIT)
            {
                EndDrawing();
                CloseWindow();
            }
            break;

        case MENU_THEMES:
            menuState = DrawThemesMenu();
            break;

        case MENU_CONTROLS:
            menuState = DrawControlsMenu();
            if (IsKeyPressed(KEY_BACKSPACE))
                menuState = MENU_MAIN;
            break;

        case MENU_CUSTOM:
            menuState = DrawCustomMenu(customSize);
            if (menuState == MENU_PLAYING)
            {
                levelCleared = 0;
                lives = 3;
                mazeSize = customSize;
                GenerateMaze(maze, mazeSize, mazeSize);
                player = { 0, 0 };
                gamePaused = false;
                SpawnEnemies(enemies, maze, player, levelCleared + 1);
            }
            break;

        case MENU_PLAYING:
        {
            if (IsKeyPressed(KEY_ESCAPE))
                gamePaused = !gamePaused;

            if (!gamePaused)
            {
                bool mazeFinished = false;

                MovePlayer(player, maze, levelCleared, mazeFinished);
                MoveEnemies(enemies, maze, dt, enemyMoveTimer);

                for (const Enemy& e : enemies)
                {
                    if (player.x == e.x && player.y == e.y)
                    {
                        lives--;
                        if (lives > 0)
                        {
                            player = { 0, 0 };
                        }
                        else
                        {
                            menuState = MENU_DEAD;
                        }
                    }
                }

                int currentLevel = levelCleared + 1;
                DrawMaze(maze, cellSize, player, enemies, currentLevel);

                DrawText(TextFormat("Lives: %d", lives), 650, 40, 25, RED);

                if (mazeFinished)
                {
                    GenerateMaze(maze, mazeSize, mazeSize);
                    player = { 0, 0 };
                    SpawnEnemies(enemies, maze, player, currentLevel);
                }
            }
            else
            {
                if (HandlePauseMenu(gamePaused, exitGame) || exitGame)
                {
                    CloseWindow();
                }
            }
        }
        break;

        case MENU_DEAD:
        {
            ClearBackground(BLACK);
            DrawText("YOU DIED", 270, 250, 60, RED);
            DrawText("Press R to Restart", 250, 350, 35, WHITE);
            DrawText("Press ESC to Quit", 270, 420, 30, GRAY);

            if (IsKeyPressed(KEY_R))
            {
                lives = 3;
                levelCleared = 0;
                player = { 0, 0 };
                GenerateMaze(maze, mazeSize, mazeSize);
                SpawnEnemies(enemies, maze, player, levelCleared + 1);
                menuState = MENU_PLAYING;
            }

            if (IsKeyPressed(KEY_ESCAPE))
            {
                CloseWindow();
            }
        }
        break;

        case MENU_EXIT:
            EndDrawing();
            CloseWindow();
        }

        EndDrawing();
    }

    CloseWindow();
}
