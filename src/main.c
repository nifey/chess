#include "game.h"
int main(){
	Game game = initializeGame();
	gameLoop(&game);
	return 0;
}
