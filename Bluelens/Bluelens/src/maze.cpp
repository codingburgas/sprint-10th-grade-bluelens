#include "../include/maze.h"
#include "../include/theme.h"
#include <stack>
#include <cstdlib>
#include <ctime>
#include <vector>

void GenerateMaze(std::vector<std::vector<Cell>>& maze, int w, int h)
{
    maze.assign(h, std::vector<Cell>(w));
    std::stack<std::pair<int, int>> s;
    int cx = 0, cy = 0;
    maze[cy][cx].visited = true;
    s.push({ cx, cy });
    int dirs[4][2] = { {0,-1},{1,0},{0,1},{-1,0} }; // up, right, down, left

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

// DRAW MAZE
void DrawMaze(const std::vector<std::vector<Cell>>& maze, int cellSize, const Player& player, const std::vector<Enemy>& enemies, int level)
{
    Theme currentTheme = GetCurrentTheme();

    if (maze.empty() || maze[0].empty()) return;

    int h = (int)maze.size();
    int w = (int)maze[0].size();

    ClearBackground(BLACK);

    // Draw cells
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
        {
            Rectangle rc = { (float)(x * cellSize), (float)(y * cellSize), (float)cellSize, (float)cellSize };
            DrawRectangleRec(rc, CLITERAL(Color){18, 18, 18, 255});
        }

    // Draw walls
    float thickness = 2.0f;
    for (int y = 0; y < h; ++y)
        for (int x = 0; x < w; ++x)
        {
            int px = x * cellSize, py = y * cellSize;
            Color wallColor = currentTheme.wallColor;
            if (maze[y][x].walls[0]) DrawLineEx({ (float)px, (float)py }, { (float)(px + cellSize), (float)py }, thickness, wallColor);
            if (maze[y][x].walls[1]) DrawLineEx({ (float)(px + cellSize), (float)py }, { (float)(px + cellSize), (float)(py + cellSize) }, thickness, wallColor);
            if (maze[y][x].walls[2]) DrawLineEx({ (float)px, (float)(py + cellSize) }, { (float)(px + cellSize), (float)(py + cellSize) }, thickness, wallColor);
            if (maze[y][x].walls[3]) DrawLineEx({ (float)px, (float)py }, { (float)px, (float)(py + cellSize) }, thickness, wallColor);
        }

    // Draw goal
    int gx = w - 1, gy = h - 1;
    DrawRectangle(gx * cellSize + 5, gy * cellSize + 5, cellSize - 10, cellSize - 10, GREEN);

    // Draw player
    DrawRectangle(player.x * cellSize + 4, player.y * cellSize + 4, cellSize - 8, cellSize - 8, currentTheme.playerColor);

    // Draw enemies
    for (const auto& e : enemies)
        DrawRectangle(e.x * cellSize + 6, e.y * cellSize + 6, cellSize - 12, cellSize - 12, currentTheme.enemyColor);

    // Draw UI: Level and Difficulty
    const char* diffText = "Easy";
    if (level >= 10) diffText = "Insane";
    else if (level >= 7) diffText = "Hard";
    else if (level >= 3) diffText = "Normal";

    DrawText(TextFormat("Level: %d", level), 20, 650, 20, RAYWHITE);
    DrawText(TextFormat("Difficulty: %s", diffText), 20, 700, 18, RAYWHITE);
    DrawText("Goal: Green square (bottom-right)", 20, 750, 14, RAYWHITE);
}

// PLAYER MOVEMENT
void MovePlayer(Player& player, const std::vector<std::vector<Cell>>& maze, int& levelCleared, bool& mazeFinished)
{
    int dx = 0, dy = 0;
    int direction = -1;

    if (IsKeyPressed(KEY_W) || IsKeyPressed(KEY_UP)) { dy = -1; direction = 0; }
    else if (IsKeyPressed(KEY_S) || IsKeyPressed(KEY_DOWN)) { dy = 1; direction = 2; }
    else if (IsKeyPressed(KEY_A) || IsKeyPressed(KEY_LEFT)) { dx = -1; direction = 3; }
    else if (IsKeyPressed(KEY_D) || IsKeyPressed(KEY_RIGHT)) { dx = 1; direction = 1; }

    if (direction != -1)
    {
        int nx = player.x + dx;
        int ny = player.y + dy;
        if (nx >= 0 && ny >= 0 && ny < (int)maze.size() && nx < (int)maze[0].size())
        {
            if (!maze[player.y][player.x].walls[direction])
            {
                player.x = nx;
                player.y = ny;
            }
        }
    }

    if (player.x == (int)maze[0].size() - 1 && player.y == (int)maze.size() - 1)
    {
        mazeFinished = true;
        levelCleared++;
    }
}

// ENEMY LOGIC
int EnemyCountForLevel(int level)
{
    if (level >= 10) return 3;
    if (level >= 7)  return 2;
    if (level >= 3)  return 1;
    return 0;
}

void SpawnEnemies(std::vector<Enemy>& enemies, const std::vector<std::vector<Cell>>& maze, const Player& player, int level)
{
    enemies.clear();
    if (maze.empty() || maze[0].empty()) return;

    int h = (int)maze.size();
    int w = (int)maze[0].size();
    int count = EnemyCountForLevel(level);

    for (int i = 0; i < count; ++i)
    {
        bool placed = false;
        for (int attempt = 0; attempt < 300 && !placed; ++attempt)
        {
            int ex = rand() % w;
            int ey = rand() % h;

            if ((ex == player.x && ey == player.y) || (ex == w - 1 && ey == h - 1)) continue;

            bool dup = false;
            for (auto& e : enemies) if (e.x == ex && e.y == ey) { dup = true; break; }
            if (dup) continue;

            enemies.push_back({ ex, ey });
            placed = true;
        }
    }
}

void MoveEnemies(std::vector<Enemy>& enemies, const std::vector<std::vector<Cell>>& maze, float dt, float& moveTimer)
{
    if (enemies.empty() || maze.empty() || maze[0].empty()) return;

    const float MOVE_INTERVAL = 0.20f;
    moveTimer += dt;
    if (moveTimer < MOVE_INTERVAL) return;
    moveTimer = 0.0f;

    int dirs[4][2] = { {0,-1}, {1,0}, {0,1}, {-1,0} };

    int h = (int)maze.size();
    int w = (int)maze[0].size();

    for (auto& e : enemies)
    {
        int x = e.x, y = e.y;
        std::vector<int> allowed;
        for (int d = 0; d < 4; ++d)
        {
            int nx = x + dirs[d][0];
            int ny = y + dirs[d][1];
            if (nx < 0 || ny < 0 || nx >= w || ny >= h) continue;
            if (!maze[y][x].walls[d]) allowed.push_back(d);
        }

        if (!allowed.empty())
        {
            int pick = allowed[rand() % allowed.size()];
            e.x = x + dirs[pick][0];
            e.y = y + dirs[pick][1];
        }
    }
}

