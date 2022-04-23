// Roguelib - src/map.h
// github.com/leftbones/roguelib

// A Note About Maps
// Maps are super neat, but right now kind of tedious to use. My plan is to build a secondary editor used for building
// maps by drawing them similar to how RexPaint works, and that would then output a matrix that could be used here,
// because building them by hand is definitely less than ideal, though it can be done in a pinch.

//#include "raylib/src/raylib.h"

typedef struct Map {
    int w;
    int h;
    int matrix[];
} Map;

/*const Map test_map = 
{
	.w = 7, .h = 7,
	.matrix = {
		201,205,205,205,205,205,187, // You can use the int index numbers
		186,  9,250,250,227,233,186, // or "nicknames" (see -> glyph.h)
		186,250,250,250,250,250,186,
		186,250,250, 64,250,250,186,
		186,250,250,250,250,250,186,
		186,250,250,250,250,250,186,
		200,205,181,196,198,205,188,
	}
};*/


// Map Drawing Functions
// ------------------------------

// Draw a matrix from a preset map, see -> `map.h`
void DrawGlyphMap(Render rs, const Map* m, int x, int y) {
	for (int col = 0; col < m->h; col++) {
		for (int row = 0; row < m->w; row++) {
			int idx = m->matrix[col * m->w + row];
			DrawGlyph(rs, idx, x+row, y+col, WHITE);
		}
	}
}

// Draw a box with a single character
// ------------------------------
void DrawBoxSimple(Render rs, int x, int y, int w, int h, int wall_glyph, int fill_glyph, Color wall_color, Color fill_color) {
	for (int col = 0; col < h; col++) {
		for (int row = 0; row < w; row++) {
			if ((col == 0 || col == h-1) || (row == 0 || row == w-1)) {
				DrawGlyph(rs, wall_glyph, x+row, y+col, fill_color);
			} else {
				DrawGlyph(rs, fill_glyph, x+row, y+col, wall_color);
			}
		}
	}
}

// Draw a box with characters for sides and corners
// ------------------------------
void DrawBoxExtra(Render rs, int x, int y, int w, int h, int wall_glyph, int corner_glyph, int fill_glyph, Color wall_color, Color corner_color, Color fill_color) {
	for (int col = 0; col < h; col++) {
		for (int row = 0; row < w; row++) {
			if ((col == 0 && row == 0) || (col == w-1 && row == h-1) || (col == 0 && row == h-1) || (col == w-1 && row == 0)) {
				DrawGlyph(rs, corner_glyph, x+row, y+col, corner_color);
			} else if ((col == 0 || col == h-1) || (row == 0 || row == w-1)) {
				DrawGlyph(rs, wall_glyph, x+row, y+col, wall_color);
			} else {
				DrawGlyph(rs, fill_glyph, x+row, y+col, fill_color);
			}
		}
	}
}

// Draw a box with characters for four sides and four corners
// ------------------------------
void DrawBoxComplex(Render rs, int x, int y, int w, int h, int wng, int weg, int wsg, int wwg, int tlg, int trg, int blg, int brg, int fill, Color wall_col, Color corner_col, Color fill_col) {
	for (int col = 0; col < h; col++) {
		for (int row = 0; row < w; row++) {
			if (col == 0 && row == 0) {

				DrawGlyph(rs, tlg, x+row, y+col, corner_col);

			} else if (row == w-1 && col == 0) {

				DrawGlyph(rs, trg, x+row, y+col, corner_col);

			} else if (row == 0 && col == h-1) {

				DrawGlyph(rs, blg, x+row, y+col, corner_col);

			} else if (row == w-1 && col == h-1) {

				DrawGlyph(rs, brg, x+row, y+col, corner_col);

			} else if (col == 0) {

				DrawGlyph(rs, wng, x+row, y+col, wall_col);

			} else if (row == w-1) {
				DrawGlyph(rs, weg, x+row, y+col, wall_col);
			} else if (col == h-1) {
				DrawGlyph(rs, wsg, x+row, y+col, wall_col);
			} else if (row == 0) {
				DrawGlyph(rs, wwg, x+row, y+col, wall_col);
			} else {
				DrawGlyph(rs, fill, x+row, y+col, fill_col);
			}
		}
	}
}
