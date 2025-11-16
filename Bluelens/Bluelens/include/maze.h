#pragma once
#ifndef MAZE_H
#define MAZE_H

#include "raylib.h"
#include <vector>

struct Cell
{
    bool visited = false;
    bool walls[4] = { true, true, true, true }; // top, right, bottom, left
};

struct Player
{
    int x = 0;
    int y = 0;
};

struct Enemy
{
    int x = 0;
    int y = 0;
};

void GenerateMaze(std::vector<std::vector<Cell>>& maze, int w, int h);

void DrawMaze(const std::vector<std::vector<Cell>>& maze, int cellSize, const Player& player, const std::vector<Enemy>& enemies, int level = 1);

void MovePlayer(Player& player, const std::vector<std::vector<Cell>>& maze, int& levelCleared, bool& mazeFinished);

int EnemyCountForLevel(int level);

void SpawnEnemies(std::vector<Enemy>& enemies, const std::vector<std::vector<Cell>>& maze, const Player& player, int level);

void MoveEnemies(std::vector<Enemy>& enemies, const std::vector<std::vector<Cell>>& maze, float dt, float& moveTimer);

#endif

