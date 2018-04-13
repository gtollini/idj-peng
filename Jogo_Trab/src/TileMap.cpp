#include "../include/TileMap.h"
#include "../include/Component.h"
#include <iostream>
#define DEBUGMENU 0


TileMap::TileMap (GameObject& associated, std::string file, TileSet* tileSet) : Component(associated){
	SetTileSet (tileSet);
	Load(file);
}


void TileMap::Load(std::string file){
	FILE *fp = fopen (file.c_str(), "r");
		if (fp == NULL){
			printf ("ERRO: Não foi possível abrir o arquivo em %s\n", file.c_str());
		}
	if (DEBUGMENU) printf ("	lendo header...\n");
	fscanf (fp, "%d,%d,%d,\n\n", &mapWidth, &mapHeight, &mapDepth);
	tileMatrix.reserve(mapWidth*mapHeight*mapDepth);
	if (DEBUGMENU) printf ("	lendo arquivo...\n");
	for (int i=0; i<mapDepth; i++){
		for (int j=0;j<mapHeight;j++){
			fgetc(fp);
			for (int k=0; k<mapWidth;k++){
				fscanf (fp, "%d,", &tileMatrix[i*mapWidth*mapHeight + j*mapWidth+k]);
				tileMatrix[i*mapWidth*mapHeight + j*mapWidth+k]--;
				if (DEBUGMENU) printf ("%d ", tileMatrix[i*mapWidth*mapHeight + j*mapWidth+k]);
				}
			if (DEBUGMENU) printf ("\n");
			}
		if (DEBUGMENU) printf ("\n");
		fgetc(fp);
		}
	fclose(fp);
}

int& TileMap::At(int x, int y, int z){
	return tileMatrix[x*mapWidth+y+z*mapWidth*mapHeight];
}

void TileMap::SetTileSet (TileSet* tileSet){
	this->tileSet=tileSet;
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
	for (int j=0;j<mapHeight;j++){
		for (int k=0; k<mapWidth;k++){
			//printf ("%d,", tileMatrix[layer*mapWidth*mapHeight + j*mapWidth+k]);
			//printf ("%d, ", j+cameraX);
			//printf ("%d, ", k+cameraX);
			tileSet->RenderTile(tileMatrix[layer*mapWidth*mapHeight + j*mapWidth+k], (float)(k+cameraX), (float)(j+cameraY));
			}
		//printf ("\n");
		}
	//printf ("\n");
}

void TileMap::Render(){
	for (int i=0; i<mapDepth; i++){
		RenderLayer(i, (int)associated.box.x, (int)associated.box.y);
	}
}

int TileMap::GetWidth(){
	return mapWidth;
}

int TileMap::GetHeight(){
	return mapHeight;
}

int TileMap::GetDepth(){
	return mapDepth;
}

bool TileMap::Is(std::string type){
	return type=="TileMap";
}




