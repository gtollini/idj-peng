#include <iostream>
#include "Sprite.h"
#ifndef TILESET_CLASS


class TileSet {
public:
	TileSet(int tileWidth, int tileHeight, std::string file);
	void RenderTile (unsigned index, float x, float y);
	int GetTileWidth ();
	int GetTileHeight ();
private:
	Sprite* tileset;
	int rows;
	int columns;
	int tileWidth;
	int tileHeight;
};






#define TILESET_CLASS
#endif
