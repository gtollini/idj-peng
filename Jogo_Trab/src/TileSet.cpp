#include <iostream>
#include "../include/TileSet.h"
#include "../include/Sprite.h"

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) : tileWidth (tileWidth), tileHeight(tileHeight){
	tileset = new Sprite(file);
	rows = tileset->GetHeight()/tileHeight;
	columns = tileset->GetWidth()/tileHeight;
}

void TileSet::RenderTile (unsigned index, float x, float y){

}
