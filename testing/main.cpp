// Roguelib Testing

#include <iostream>
#include <vector>

#include "../src/roguelib.h"
#include "main.h"
#include "util.h"

using namespace std;

typedef struct Player {
    int x;
    int y;
    int g;
    Color c;
    int health;
    int magic;
    int level;
    int exp;
    int progress;
    int prog_max;
} Player;

typedef struct Goblin {
    int x;
    int y;
    int g;
    Color c;
    int health;
    int magic;
    int level;
} Goblin;

typedef struct Tile {
    int x;
    int y;
    int g;
    Color c;
} Tile;

bool TileIsFree(Render rs, Tile tiles[], int x, int y) {
    if (x < 0 || x > rs.max_tiles_x - 1 || y < 0 || y > rs.max_tiles_y - 1) { return false; }
    if (tiles[y * rs.max_tiles_x + x].g == PERIOD) { return true; }
    return false;
}

int main() {
    InitWindow(800, 800, "Roguelib Testing");
    SetTargetFPS(60);
    srand(time(NULL));

    Texture2D tileset = LoadTexture("assets/tileset.png");
    Render RenderSystem = RenderSystemInit(800, 800, DARKER_GRAY, 16, tileset);

    Tile* tiles = new Tile[RenderSystem.max_tiles_x * RenderSystem.max_tiles_y];
    vector<Goblin> enemies;

    for (int y = 0; y < RenderSystem.max_tiles_y; y++) {
        for (int x = 0; x < RenderSystem.max_tiles_x; x++) {
            if (DiceRoll(4)) {
                Tile tile = {
                    .x = x,
                    .y = y,
                    .g = HASH,
                    .c = NORMAL_GRAY
                };
                tiles[y * RenderSystem.max_tiles_x + x] = tile;
            } else {
                Tile tile = {
                    .x = x,
                    .y = y,
                    .g = PERIOD,
                    .c = DARK_GRAY
                };
                tiles[y * RenderSystem.max_tiles_x + x] = tile;
                
                // Enemies
                if (DiceRoll(60)) {
                    Goblin goblin = {
                        .x = x,
                        .y = y,
                        .g = LOWER_G,
                        .c = LIGHT_GRAY,
                        .health = 50,
                        .magic = 5,
                        .level = 1,
                    };
                    enemies.push_back(goblin);
                }
            }
        }
    }

    Player player = {
        .x = RenderSystem.center_x,
        .y = RenderSystem.center_y,
        .g = SYM_2,
        .c = WHITE,
        .health = 100,
        .magic = 100,
        .level = 1,
        .exp = 0,
        .progress = 0,
        .prog_max = 0,
    };

    int update_tick = 0;
    int update_interval = 5;

    bool enemies_move = false;
    bool redraw_screen = true;

    while (!WindowShouldClose()) {
        // Update

        // Player Movement
        if (update_tick == 0) {
            if (IsKeyDown(KEY_K) && TileIsFree(RenderSystem, tiles, player.x, player.y-1)) {
                player.y -= 1;
                player.progress += 1;
                if (player.progress > player.prog_max) { player.prog_max += 1; }
                update_tick = update_interval;
            }
            else if (IsKeyDown(KEY_J) && TileIsFree(RenderSystem, tiles, player.x, player.y+1)) {
                player.y += 1;
                player.progress -= 1;
                update_tick = update_interval;
                enemies_move = true;
                redraw_screen = true;
            }
            else if (IsKeyDown(KEY_H) && TileIsFree(RenderSystem, tiles, player.x-1, player.y)) { player.x -= 1; update_tick = update_interval; }
            else if (IsKeyDown(KEY_L) && TileIsFree(RenderSystem, tiles, player.x+1, player.y)) { player.x += 1; update_tick = update_interval; }
        } else {
            update_tick--;
        }

        // Enemy Movement
        if (enemies_move) {
            for (Goblin enemy: enemies) {
                bool has_moved = false;
                while (!has_moved) {
                    if (TileIsFree(RenderSystem, tiles, enemy.x, enemy.y - 1) && DiceRoll(6)) { enemy.y -= 1; has_moved = true; }
                    else if (TileIsFree(RenderSystem, tiles, enemy.x, enemy.y + 1) && DiceRoll(6)) { enemy.y += 1; has_moved = true; }
                    else if (TileIsFree(RenderSystem, tiles, enemy.x - 1, enemy.y) && DiceRoll(6)) { enemy.x -= 1; has_moved = true; }
                    else if (TileIsFree(RenderSystem, tiles, enemy.x + 1, enemy.y) && DiceRoll(6)) { enemy.x += 1; has_moved = true; }
                }
                cout << "Goblin has moved" << endl;
            }
        }

        // Draw
        BeginDrawing();
        if (redraw_screen) {
            ClearBackground(RenderSystem.bg_color);

            // Walls
            for (int i = 0; i < RenderSystem.max_tiles_x * RenderSystem.max_tiles_y; i++) {
                Tile* tile = &tiles[i];
                DrawGlyph(RenderSystem, tile->g, tile->x, tile->y, tile->c, true);
            }

            // Enemies
            for(Goblin enemy : enemies) {
                DrawGlyph(RenderSystem, enemy.g, enemy.x, enemy.y, enemy.c, true);
            }

            // Player
            DrawGlyph(RenderSystem, player.g, player.x, player.y, player.c, true);

            // UI
            for (int y = 0; y < 4; y++) {
                for (int x = 0; x < RenderSystem.max_tiles_x; x++) {
                    DrawGlyph(RenderSystem, FULL_BLOCK, x, y, BLACK, true);
                }
            }

            const char *player_hp = TextFormat("%i", player.health);
            PrintText(RenderSystem, "HP ", 1, 1, WHITE, false);
            PrintText(RenderSystem, player_hp, 4, 1, BLOOD_RED, false);

            const char *player_mp = TextFormat("%i", player.magic);
            PrintText(RenderSystem, "MP ", 1, 2, WHITE, false);
            PrintText(RenderSystem, player_mp, 4, 2, MAGIC_BLUE, false);

            const char *player_prog = TextFormat("%i", player.prog_max);
            PrintText(RenderSystem, player_prog, RenderSystem.center_x, 1, WHITE, false);

            const char *player_lvl = TextFormat("%i", player.level);
            int rx = RenderSystem.max_tiles_x - 6;
            PrintText(RenderSystem, "LVL ", rx, 1, WHITE, false);
            PrintText(RenderSystem, player_lvl, rx + 4, 1, LIGHT_GRAY, false);

            const char *player_exp = TextFormat("%i", player.exp);
            PrintText(RenderSystem, "EXP ", rx, 2, WHITE, false);
            PrintText(RenderSystem, player_exp, rx + 4, 2, LIGHT_GRAY, false);
        }
        EndDrawing();
    }

    return 0;
}
