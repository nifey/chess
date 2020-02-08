#include "piece.h"

struct Board{
	Piece *pieces;
	Color Turn;
	int GameOver;
};
typedef struct Board Board;

Board initializeBoard();

void initializePieces(Piece *pieces);

int isGameOver(Board b);

int getWinner(Board b);

int isCellOccupiable(Board b, Color c, char file, int rank);

Piece getPieceByType(Board b, Color c, Type t);

int isValidCell(char file, int rank);

int isValidMove(Board b, char oldFile, int oldRank, char newFile, int newRank);
