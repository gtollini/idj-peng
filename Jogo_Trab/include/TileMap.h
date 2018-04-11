#include <iostream>
#include "GameObject.h"
#include "TileSet.h"
#ifndef TILEMAP_CLASS

class TileMap {
public:
	TileMap (GameObject& associated, std::string file, TileSet* tileSet);
	void Load (std::string file);
	void SetTileSet (TileSet* tileSet);
	int& At (int x, int y, int z=0);
	void Render ();
	void RenderLayer (int layer, int cameraX, int cameraY);
	int GetWidth();
	int GetHeight();
	int GetDepth;
private:
	std::vector<int> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
};


#define TILEMAP_CLASS
#endif
