#ifndef _Game__H
#define _Game__H
const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;
#include "SDL.h"
#include "SDL_image.h"
#include <SDL_ttf.h>
#include <iostream>
#include <vector>


const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;


const int paddleHeight = 120;
const int paddleWidth = 25;

const int ballWidth = 15;
const int ballHeight = 15;

const int paddleMove = 10;
class Game {
public:
	Game();
	~Game();

	void init();
	void quit();
	
	void handleEvents();
	void checkCollision();
	void render();
	

	bool running() {
		return isRunning;
	}
private:
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif