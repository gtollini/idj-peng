#include "../include/TileMap.h"
#include "../include/Component.h"
#include "../include/Camera.h"

#include <iostream>
#define DEBUGMENU 0
#define PAR 1

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
	fscanf (fp, "%d,%d,%d,\n\n", &mapHeight, &mapWidth, &mapDepth);
	tileMatrix.reserve(mapWidth*mapHeight*mapDepth);
	if (DEBUGMENU) printf ("	lendo arquivo...\n");

	for (int i=0; i<mapDepth*mapHeight*mapWidth; i++){
		fscanf (fp, "%d,", &tileMatrix[i]);
		tileMatrix[i]--;
		if (DEBUGMENU) printf ("%d ", tileMatrix[i]);
		//fgetc(fp);
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
			tileSet->RenderTile(tileMatrix[layer*mapWidth*mapHeight + j*mapWidth+k], (float)(k*tileSet->GetTileWidth()-cameraX), (float)(j*tileSet->GetTileHeight()-cameraY));
			}
		}
}

void TileMap::Render(){
	for (int i=0; i<mapDepth; i++){
		RenderLayer(i, (int)associated.box.x+Camera::GetInstance().pos.x*(1+PAR*i), (int)associated.box.y+Camera::GetInstance().pos.y*(1+PAR*i));
	}
}

/*void TileMap::Render(float cameraX, float cameraY){
	for (int i=0; i<mapDepth; i++){
			//printf ("Ax = %f	Cx=%f\n", associated.box.x, cameraX);
			RenderLayer(i, (int)(associated.box.x+cameraX), (int)(associated.box.y+cameraY));
		}
}*/

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




