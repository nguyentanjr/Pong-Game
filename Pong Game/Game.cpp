#include"Game.h"
#include<iostream>

int ballX = SCREEN_WIDTH / 2 - ballWidth / 2;  
int ballY = SCREEN_HEIGHT / 2 - ballHeight / 2;

int paddleLeftX = 0;
int paddleLeftY = SCREEN_HEIGHT / 2 - paddleHeight / 2; 
int paddleRightX = SCREEN_WIDTH - paddleWidth;
int paddleRightY = SCREEN_HEIGHT / 2 - paddleHeight / 2;

int ballMoveX = 3;
int ballMoveY = 3;

Game::Game(){}

Game::~Game(){}


void Game::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
		if (window != NULL) {
			std::cout << "Window created!";
			renderer = SDL_CreateRenderer(window, -1, 0);
			if (renderer != NULL) {
				std::cout << "Renderer created!";
				isRunning = true;
			}
		}
	}
	else isRunning = false;
}


void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
	const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
	if (keyboardState[SDL_SCANCODE_W] != 0 && paddleLeftY > 0) {
		paddleLeftY -= paddleMove;
	}
	if (keyboardState[SDL_SCANCODE_UP] != 0 && paddleRightY > 0) {
		paddleRightY -= paddleMove;
	}
	if (keyboardState[SDL_SCANCODE_S] != 0 && paddleLeftY + paddleHeight < SCREEN_HEIGHT) {
		paddleLeftY += paddleMove;
	}
	if (keyboardState[SDL_SCANCODE_DOWN] != 0 && paddleRightY + paddleHeight < SCREEN_HEIGHT) {
		paddleRightY += paddleMove;
	}
}


void Game::render() {
	SDL_RenderClear(renderer);
	SDL_Surface* tmpBackground = IMG_Load("kei2.png");
	SDL_Texture* textureBackground = SDL_CreateTextureFromSurface(renderer, tmpBackground);
	SDL_RenderCopy(renderer, textureBackground, NULL, NULL);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_Rect paddleLeft = { paddleLeftX,paddleLeftY,paddleWidth,paddleHeight };
	SDL_Rect paddleRight = { paddleRightX,paddleRightY,paddleWidth,paddleHeight };

	SDL_RenderFillRect(renderer, &paddleLeft);
	SDL_RenderFillRect(renderer, &paddleRight);

	SDL_Rect ball = { ballX, ballY, ballWidth, ballHeight };
	SDL_RenderFillRect(renderer, &ball);

	SDL_RenderPresent(renderer);
}

void Game::checkCollision() {

	ballX += ballMoveX;
	ballY += ballMoveY;
	if (ballY <= 0 || ballY + ballHeight > SCREEN_HEIGHT)ballMoveY = -ballMoveY;
	if (ballX < 0 || ballY < 0 || ballX > SCREEN_WIDTH || ballY > SCREEN_HEIGHT)isRunning = false;

	if ((ballX <= paddleLeftX + paddleWidth && ballY > paddleLeftY && ballY < paddleLeftY + paddleHeight)||
		(ballX + ballWidth >= paddleRightX && ballY + ballWidth > paddleRightY && ballY < paddleRightY + paddleHeight)) ballMoveX = -ballMoveX;
}

void Game::quit() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}