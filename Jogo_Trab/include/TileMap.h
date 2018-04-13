#ifndef TILEMAP_CLASS
#define TILEMAP_CLASS

#include <iostream>
#include "GameObject.h"
#include "TileSet.h"
#include "Component.h"


class TileMap : public Component {
public:
	TileMap (GameObject& associated, std::string file, TileSet* tileSet);
	void Load (std::string file);
	void SetTileSet (TileSet* tileSet);
	int& At (int x, int y, int z=0);
	void Render ();
	void RenderLayer (int layer, int cameraX, int cameraY);
	int GetWidth();
	int GetHeight();
	int GetDepth();
	bool Is (std::string type);
private:
	std::vector<int> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;
};



#endif
