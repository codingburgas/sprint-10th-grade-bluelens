#pragma once
#ifndef MAZE_H
#define MAZE_H

#include "raylib.h"
#include <vector>

struct Cell
{
    bool visited = false;
    bool walls[4] = { true, true, true, true };
};

struct Player
{
    int x, y;
};

struct Enemy
{
    int x, y;
};

void GenerateMaze(std::vector<std::vector<Cell>>& maze, int w, int h);
void DrawMaze(const std::vector<std::vector<Cell>>& maze, int cellSize, const Player& player, const std::vector<Enemy>& enemies);
void MovePlayer(Player& player, const std::vector<std::vector<Cell>>& maze, int& levelCleared, bool& mazeFinished);

#endif
