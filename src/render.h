// Roguelib - src/render.h
// github.com/leftbones/roguelib

//#include "raylib/src/raylib.h"

// RenderSystem - used to render glyphs to the game window
typedef struct RenderSystem {
    int screen_w;           // width of the screen in pixels
    int screen_h;           // height of the screen in pixels
    Color bg_color;         // background color of the screen
    Texture2D tileset;      // path to the tileset image
    int tile_size;          // size of each tile in pixels
    int max_tiles_x;        // horizontal max tiles (screen_w / tile_size)
    int max_tiles_y;        // vertical max tiles (screen_h / tile_size)
    int center_x;           // center tile x position (in tiles)
    int center_y;           // center tile y position (in tiles)
    Rectangle frame_rec;    // rectangle used to get glyphs from the tileset
    Glyph glyph_map[256];   // array of all glyphs in the tileset
} Render;


// Initialize the RenderSystem, only needs to be done once
Render RenderSystemInit(int screen_w, int screen_h, Color bg_color, int tile_size, Texture2D tileset) {
    // Create new RenderSystem
    Render rs;

    // Build the glyph map
    for (int y = 0; y < 16; y++) {
        for (int x = 0; x < 16; x++) {
            Glyph g;
            g.x = y;
            g.y = x;
            rs.glyph_map[x * 16 + y] = g;
        }
    }

    // Initialize RenderSystem with passed parameters
    rs.screen_w = screen_w;
    rs.screen_h = screen_h;
    rs.bg_color = bg_color;
    rs.tileset = tileset;
    rs.tile_size = tile_size;

    rs.max_tiles_x = screen_w / tile_size;
    rs.max_tiles_y = screen_h / tile_size;
    rs.center_x = rs.max_tiles_x / 2 - 1;
    rs.center_y = rs.max_tiles_y / 2 - 1;
    rs.frame_rec = (Rectangle){ 0.0f, 0.0f, (float)tileset.width / tile_size, (float)tileset.height / tile_size };

    return rs;
}


// Draw a glyph to the screen using the passed index, position, and color
void DrawGlyph(Render rs, int idx, int x, int y, Color col, bool overlay) {
    Vector2 pos = { (float)x * rs.tile_size, (float)y * rs.tile_size };

    rs.frame_rec.x = rs.tile_size * rs.glyph_map[idx].x;
    rs.frame_rec.y = rs.tile_size * rs.glyph_map[idx].y;

    if (overlay) { DrawRectangle((float)x * rs.tile_size, (float)y * rs.tile_size, rs.tile_size, rs.tile_size, rs.bg_color); }
    DrawTextureRec(rs.tileset, rs.frame_rec, pos, col);
}


// Print a "string" to the screen by matching each character in the passed string to a glyph and drawing them in sequence
void PrintText(Render rs, const char* text, int x, int y, Color col, bool overlay) {
    // Iterate through the characters of the text
    for (int i = 0; i < strlen(text); i++) {
        // Find the index of the glyph matching the current character
        char idx = GetGlyphIndexByChar(text[i]);

        // Erase any glyphs that are at the position we want to print to prevent overlapping
        if (overlay) { DrawRectangle((x + i) * rs.tile_size, y * rs.tile_size, rs.tile_size, rs.tile_size, rs.bg_color); }

        // Draw the glyph
        DrawGlyph(rs, idx, x+i, y, col, overlay);
    }
}
