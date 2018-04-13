#ifndef TILESET_CLASS
#define TILESET_CLASS

#include <iostream>
#include "Sprite.h"



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







#endif
