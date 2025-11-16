#include "raylib.h"
#include "../include/maze.h"
#include "../include/mainMenu.h"
#include "../include/howToPlay.h"
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

    const int width = 20, height = 20, cellSize = 30;

    std::vector<std::vector<Cell>> maze;
    Player player{ 0, 0 };
    std::vector<Enemy> enemies;

    float enemyMoveTimer = 0.0f;

    // Initial setup
    GenerateMaze(maze, width, height);
    int currentLevel = levelCleared + 1;
    SpawnEnemies(enemies, maze, player, currentLevel);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        BeginDrawing();
        ClearBackground(DARKGRAY);

        switch (menuState)
        {
        case MENU_MAIN:
            menuState = DrawMainMenu();
            break;

        case MENU_CONTROLS:
            menuState = DrawControlsMenu();
            if (IsKeyPressed(KEY_BACKSPACE))
                menuState = MENU_MAIN;
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

                currentLevel = levelCleared + 1;
                DrawMaze(maze, cellSize, player, enemies, currentLevel);

                DrawText(TextFormat("Lives: %d", lives), 650, 40, 25, RED);


                if (mazeFinished)
                {
                    GenerateMaze(maze, width, height);
                    player = { 0, 0 };

                    currentLevel = levelCleared + 1;
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

                GenerateMaze(maze, width, height);
                currentLevel = levelCleared + 1;
                SpawnEnemies(enemies, maze, player, currentLevel);

                menuState = MENU_PLAYING;
            }

            if (IsKeyPressed(KEY_ESCAPE))
            {
                CloseWindow();
                return 0;
            }

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

