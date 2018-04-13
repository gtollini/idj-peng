#include <iostream>
#include "../include/TileSet.h"
#include "../include/Sprite.h"



TileSet::TileSet(int tileWidth, int tileHeight, std::string file) : tileWidth (tileWidth), tileHeight(tileHeight){
	GameObject *tileSetObject = new GameObject();
	tileset =new Sprite(file, *tileSetObject);
	rows = tileset->GetHeight()/tileHeight;
	columns = tileset->GetWidth()/tileWidth;
	delete tileSetObject;
}

void TileSet::RenderTile (unsigned index, float x, float y){
	if (index < rows*columns){
		tileset->Render(tileWidth*(index % rows), tileHeight*(index / rows),tileHeight, tileWidth,  (int) x*tileWidth,  (int) y*tileHeight);
	}
}

int TileSet::GetTileWidth () {
	return tileWidth;
}

int TileSet::GetTileHeight () {
	return tileWidth;
}
