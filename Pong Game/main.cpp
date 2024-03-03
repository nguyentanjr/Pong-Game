#include"Game.h"

Game* game = nullptr;

int main(int argc, char* argv[]) {
	game = new Game;
	game->init();
	while (game->running()){
		game->handleEvents();
		game->render();
		game->checkCollision();

	}

	game->quit();
	return 0;
}