#include "board.h"

struct game{
	Board gameBoard;
	int display;
};
typedef struct game Game;

Game initializeGame();

void gameLoop(Game *game);

void exitGame(Game *game);

void displayBoard(Game *game);

void displayBoardInTerminal(Board *board);

void getInputAndMove(Game *game);
