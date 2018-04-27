#include "../include/InputManager.h"
#include "SDL2/SDL.h"
#include <string>

#include <iostream>

InputManager& InputManager::GetInstance(){
	static InputManager im;
	return im;
}

InputManager::InputManager(){
	for (int i=0; i<6; i++){
		mouseState[i] = false;
		mouseUpdate[i]	= 0;
	}

	for (int j=0; j<416; j++){
		keyState[j] 	= false;
		keyUpdate[j] 	= 0;
}
	updateCounter =0;

	quitRequested = false;

	mouseX=0;
	mouseY=0;}
InputManager::~InputManager(){

}



void InputManager::Update(){
	SDL_Event event;


	quitRequested=0;
	updateCounter++;
	while (SDL_PollEvent(&event)){
	 if (event.key.repeat==0){
		switch (event.type){

			case(SDL_KEYDOWN):
				if (event.key.keysym.sym>0x3FFFFF81){
					keyState [event.key.keysym.sym - 0x3FFFFF81] = true;
					keyUpdate[event.key.keysym.sym - 0x3FFFFF81] = updateCounter;
				}
				else{
					keyState [event.key.keysym.sym] = true;
					keyUpdate[event.key.keysym.sym] = updateCounter;
				}


			break;

			case(SDL_KEYUP):
						if (event.key.keysym.sym>0x3FFFFF81){
							keyState [event.key.keysym.sym - 0x3FFFFF81] = false;
							keyUpdate[event.key.keysym.sym - 0x3FFFFF81] = updateCounter;
						}
						else{
							keyState [event.key.keysym.sym] = false;
							keyUpdate[event.key.keysym.sym] = updateCounter;
						}

			break;

			case(SDL_MOUSEBUTTONDOWN):
				mouseState[event.button.button] = true;
				mouseUpdate[event.button.button] = updateCounter;
			break;

			case(SDL_MOUSEBUTTONUP):
				mouseState[event.button.button] = false;
				mouseUpdate[event.button.button] = updateCounter;
			break;

			case(SDL_QUIT):
				quitRequested = true;
			break;}
		SDL_GetMouseState(&mouseX, &mouseY);
	}
	}
}


bool InputManager::KeyPress(int key){
	int index=(key<0x3FFFFF81) ? (key) : (key- 0x3FFFFF81);
	return keyState[index] && (keyUpdate[index]==updateCounter);
}
bool InputManager::KeyRelease(int key){
	int index=(key<0x3FFFFF81) ? (key) : (key- 0x3FFFFF81);
	return !keyState[index] && (keyUpdate[index]==updateCounter);
}
bool InputManager::IsKeyDown(int key){
	int index=(key<0x3FFFFF81) ? (key) : (key- 0x3FFFFF81);
	return keyState[index];
}

bool InputManager::MousePress(int button){
	return mouseState[button] && (mouseUpdate[button]==updateCounter);
}
bool InputManager::MouseRelease(int button){
	return !mouseState[button] && (mouseUpdate[button]==updateCounter);
}
bool InputManager::IsMouseDown(int button){
	return mouseState[button];
}



int InputManager::GetMouseX(){
	return mouseX;
}
int InputManager::GetMouseY(){
	return mouseY;
}

bool InputManager::QuitRequested(){
	return quitRequested;
}
