#include <stdio.h>
#include <stdlib.h>
#include "game.h"

Game initializeGame(){
	Game game;
	game.gameBoard = initializeBoard();
	game.display = 1;
	return game;
}

void gameLoop(Game *game){
	while(game->gameBoard.GameOver==0){
		system("clear");
		displayBoard(game);
		getInputAndMove(game);
	}
	return;
}

void exitGame(Game *game){
	return;
}

void displayBoard(Game *game){
	if(game->display == 1){
		displayBoardInTerminal(&game->gameBoard);
	}
}

//TODO: add option to invert the display based on turn
void displayBoardInTerminal(Board *board){
	char displayBoard[8][8];
	//Prepare board for displaying 
	int i,j;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			displayBoard[i][j]=' ';
		}
	}
	Piece *currentPiece;
	for(i=0;i<32;i++){
		currentPiece = &board->pieces[i];
		if(currentPiece->InBoard == 0){
			continue;
		}
		if(currentPiece->Color == white){
			switch(currentPiece->Type){
				case pawn:
					displayBoard[8-currentPiece->Rank][currentPiece->File - 'a'] = 'P';
					break;
				case knight:
					displayBoard[8-currentPiece->Rank][currentPiece->File - 'a'] = 'N';
					break;
				case bishop:
					displayBoard[8-currentPiece->Rank][currentPiece->File - 'a'] = 'B';
					break;
				case rook:
					displayBoard[8-currentPiece->Rank][currentPiece->File - 'a'] = 'R';
					break;
				case queen:
					displayBoard[8-currentPiece->Rank][currentPiece->File - 'a'] = 'Q';
					break;
				case king:
					displayBoard[8-currentPiece->Rank][currentPiece->File - 'a'] = 'K';
					break;
			}
		} else {
			switch(currentPiece->Type){
				case pawn:
					displayBoard[8-currentPiece->Rank][currentPiece->File - 'a'] = 'p';
					break;
				case knight:
					displayBoard[8-currentPiece->Rank][currentPiece->File - 'a'] = 'n';
					break;
				case bishop:
					displayBoard[8-currentPiece->Rank][currentPiece->File - 'a'] = 'b';
					break;
				case rook:
					displayBoard[8-currentPiece->Rank][currentPiece->File - 'a'] = 'r';
					break;
				case queen:
					displayBoard[8-currentPiece->Rank][currentPiece->File - 'a'] = 'q';
					break;
				case king:
					displayBoard[8-currentPiece->Rank][currentPiece->File - 'a'] = 'k';
					break;
			}
		}
	}
	
	//Display board
	printf("-------------------\n");
	for(i=0;i<8;i++){
		printf("%d |", 8-i);
		for(j=0;j<8;j++){
			printf("%c|", displayBoard[i][j]);
		}
		printf("\n");
	}
	printf("-------------------\n  |");
	for(j=0;j<8;j++){
		printf("%c|", j+'a');
	}
	printf("\n");

	//If game not over Print the current player
	//If game over Print the winner
	if(board->GameOver == 0){
		if(board->Turn == white){
			printf("White's turn\nEnter move: ");
		} else {
			printf("Black's turn\nEnter move: ");
		}
	}
}

void getInputAndMove(Game *game){
	int oldRank, newRank;
	char oldFile, newFile;
	scanf(" %c", &oldFile);
	scanf(" %d", &oldRank);
	scanf(" %c", &newFile);
	scanf(" %d", &newRank);
	while(!isValidCell(oldFile, oldRank) || !isValidCell(newFile, newRank)|| !isValidMove(game->gameBoard, oldFile, oldRank, newFile, newRank)){
		if(!isValidCell(oldFile, oldRank)){
			printf("Invalid cell %c%d\n", oldFile, oldRank);
		} else if(!isValidCell(newFile, newRank)){
			printf("Invalid cell %c%d\n", newFile, newRank);
		} else {
			printf("Invalid move\n");
		}
		printf("Enter move: ");
		scanf(" %c", &oldFile);
		scanf(" %d", &oldRank);
		scanf(" %c", &newFile);
		scanf(" %d", &newRank);
	}
	move(game->gameBoard, oldFile, oldRank, newFile, newRank);
	game->gameBoard.Turn = (game->gameBoard.Turn == white)? black: white;
}
