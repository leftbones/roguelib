// wasteland/render.h

// Glyph + RenderSystem Structs
// ------------------------------

// Keeps track of screen dimensions, tilesets, tileset parameters, and the array of Glyph objects
typedef struct RenderSystem {
	int screen_w;
	int screen_h;

	Texture2D tileset;
	int tile_size;
	int max_tiles_x;
	int max_tiles_y;
	int center_x;
	int center_y;
	Rectangle frame_rec;

	Glyph glyph_map[256];
} Render;


// Render Functions
// ------------------------------

// Initializes a new RenderSystem, could probably be done with a constructor instead
Render InitRenderSystem(int scrn_w, int scrn_h, int tsize, Texture2D tset) {
	// Create RenderSystem
	Render rs;

	// Build glyphmap
	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 16; x++) {
			Glyph g;
			g.x = y;
			g.y = x;
			rs.glyph_map[x * 16 + y] = g;
		}
	}

	// Finish initialization
	rs.tileset = tset;
	rs.screen_w = scrn_w;
	rs.screen_h = scrn_h;
	rs.tile_size = tsize;
	rs.max_tiles_x = scrn_w / tsize;
	rs.max_tiles_y = scrn_h / tsize;
	rs.center_x = rs.max_tiles_x / 2 - 1;
	rs.center_y = rs.max_tiles_y / 2 - 1;
	rs.frame_rec = (Rectangle){ 0.0f, 0.0f, (float)tset.width/tsize, (float)tset.height/tsize };

	return rs;
}

// Draw a Glyph to the screen by passing in the index (int or defined name), position, and color
// It figures out the tile position on the screen grid, then adjusts the frame_rec of the RenderSystem to where the Glyph is
// located, then calls DrawTextureRec (raylib) to draw it to the screen at the position
void DrawGlyph(Render rs, int idx, int x, int y, Color c) {
	Vector2 pos = { x * rs.tile_size, y * rs.tile_size };

	rs.frame_rec.x = rs.tile_size * rs.glyph_map[idx].x;
	rs.frame_rec.y = rs.tile_size * rs.glyph_map[idx].y;

	DrawTextureRec(rs.tileset, rs.frame_rec, pos, c);
}


// Prints "strings" of text to the screen grid by matching each character in the passed string to its glyph counterpart,
// then drawing those glyphs in sequence -- May expand this later on to use a separate texture for text specifically in order
// to support more text characters and to be able to replace text characters in the standard texture with graphics and not
// lose the ability to print readable text as a side effect.
void PrintText(Render rs, char* text, int x, int y, Color c) {
	for (int i = 0; i < strlen(text); i++) {
		char idx = GetGlyphIndexByChar(text[i]);
		DrawGlyph(rs, idx, x+i, y, c);
	}
}
