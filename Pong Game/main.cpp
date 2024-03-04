#include"Game.h"

Game* game = nullptr;
Uint32 frameStart;
int frameTime;

int main(int argc, char* argv[]) {
	game = new Game;
	game->init();
	while (game->running()){
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->render();
		game->checkCollision();
		frameTime = SDL_GetTicks() - frameStart;

		if (FRAME_DELAY > frameTime) {
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}

	game->quit();
	return 0;
}