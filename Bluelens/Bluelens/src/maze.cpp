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
        auto [x, y] = s.top();
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
    for (int y = 0; y < maze.size(); ++y)
    {
        for (int x = 0; x < maze[0].size(); ++x)
        {
            int px = x * cellSize, py = y * cellSize;
            if (maze[y][x].walls[0]) DrawLine(px, py, px + cellSize, py, GRAY);
            if (maze[y][x].walls[1]) DrawLine(px + cellSize, py, px + cellSize, py + cellSize, GRAY);
            if (maze[y][x].walls[2]) DrawLine(px, py + cellSize, px + cellSize, py + cellSize, GRAY);
            if (maze[y][x].walls[3]) DrawLine(px, py, px, py + cellSize, GRAY);
        }
    }

    DrawRectangle(player.x * cellSize + 3, player.y * cellSize + 3, cellSize - 6, cellSize - 6, BLUE);
    for (auto& e : enemies)
        DrawRectangle(e.x * cellSize + 3, e.y * cellSize + 3, cellSize - 6, cellSize - 6, RED);

}

void MovePlayer(Player& player, const std::vector<std::vector<Cell>>& maze, int& levelCleared, bool& mazeFinished)
{
    int dx = 0, dy = 0;
    if (IsKeyPressed(KEY_W)) dy = -1;
    else if (IsKeyPressed(KEY_S)) dy = 1;
    else if (IsKeyPressed(KEY_A)) dx = -1;
    else if (IsKeyPressed(KEY_D)) dx = 1;

    int nx = player.x + dx;
    int ny = player.y + dy;
    if (nx >= 0 && ny >= 0 && ny < maze.size() && nx < maze[0].size() && !maze[player.y][player.x].walls[(dx == 1) ? 1 : (dx == -1) ? 3 : (dy == 1) ? 2 : 0])
    {
        player.x = nx;
        player.y = ny;
    }

    if (player.x == maze[0].size() - 1 && player.y == maze.size() - 1)
    {
        mazeFinished = true;
        levelCleared++;
    }
}
