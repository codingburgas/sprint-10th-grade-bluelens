#include "../include/maze.h"
#include <stack>
#include <cstdlib>

void GenerateMaze(std::vector<std::vector<Cell>>& maze, int w, int h)
{
    maze.assign(h, std::vector<Cell>(w));
    std::stack<std::pair<int, int>> s;
    int cx = 0, cy = 0;
    maze[cy][cx].visited = true;
    s.push({ cx, cy });
    int dirs[4][2] = { {0,-1},{1,0},{0,1},{-1,0} };

    while (!s.empty())
    {
        auto cell = s.top();
        int x = cell.first;
        int y = cell.second;
        std::vector<int> neigh;
        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dirs[i][0];
            int ny = y + dirs[i][1];
            if (nx >= 0 && ny >= 0 && nx < w && ny < h && !maze[ny][nx].visited)
                neigh.push_back(i);
        }

        if (!neigh.empty())
        {
            int dir = neigh[rand() % neigh.size()];
            int nx = x + dirs[dir][0];
            int ny = y + dirs[dir][1];
            maze[y][x].walls[dir] = false;
            maze[ny][nx].walls[(dir + 2) % 4] = false;
            maze[ny][nx].visited = true;
            s.push({ nx, ny });
        }
        else s.pop();
    }
}

void DrawMaze(const std::vector<std::vector<Cell>>& maze, int cellSize, const Player& player, const std::vector<Enemy>& enemies)
{
    // Safety check
    if (maze.empty() || maze[0].empty()) return;

    for (int y = 0; y < (int)maze.size(); ++y)
    {
        for (int x = 0; x < (int)maze[0].size(); ++x)
        {
            int px = x * cellSize, py = y * cellSize;
            if (maze[y][x].walls[0]) DrawLine(px, py, px + cellSize, py, GRAY);
            if (maze[y][x].walls[1]) DrawLine(px + cellSize, py, px + cellSize, py + cellSize, GRAY);
            if (maze[y][x].walls[2]) DrawLine(px, py + cellSize, px + cellSize, py + cellSize, GRAY);
            if (maze[y][x].walls[3]) DrawLine(px, py, px, py + cellSize, GRAY);
        }
    }

    // Bounds check for player drawing
    if (player.x >= 0 && player.x < (int)maze[0].size() &&
        player.y >= 0 && player.y < (int)maze.size())
    {
        DrawRectangle(player.x * cellSize + 3, player.y * cellSize + 3, cellSize - 6, cellSize - 6, BLUE);
    }

    for (const auto& e : enemies)
    {
        if (e.x >= 0 && e.x < (int)maze[0].size() &&
            e.y >= 0 && e.y < (int)maze.size())
        {
            DrawRectangle(e.x * cellSize + 3, e.y * cellSize + 3, cellSize - 6, cellSize - 6, RED);
        }
    }
}

void MovePlayer(Player& player, const std::vector<std::vector<Cell>>& maze, int& levelCleared, bool& mazeFinished)
{
    int dx = 0, dy = 0;
    int direction = -1;

    if (IsKeyPressed(KEY_W)) { dy = -1; direction = 0; }
    else if (IsKeyPressed(KEY_S)) { dy = 1; direction = 2; }
    else if (IsKeyPressed(KEY_A)) { dx = -1; direction = 3; }
    else if (IsKeyPressed(KEY_D)) { dx = 1; direction = 1; }

    if (direction != -1)
    {
        int nx = player.x + dx;
        int ny = player.y + dy;

        if (nx >= 0 && ny >= 0 && ny < maze.size() && nx < maze[0].size())
        {
            // Check if wall exists in that direction
            if (!maze[player.y][player.x].walls[direction])
            {
                player.x = nx;
                player.y = ny;
            }
        }
    }
    // Check win condition
    if (player.x == (int)maze[0].size() - 1 && player.y == (int)maze.size() - 1)
    {
        mazeFinished = true;
        levelCleared++;
    }
}
