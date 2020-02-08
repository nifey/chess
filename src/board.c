#include <stdlib.h>
#include "board.h"

Board initializeBoard(){
	Board board;
	board.Turn = white;
	board.GameOver = 0;
	Piece *pieces = (Piece* ) malloc (sizeof(Piece)*32);
	initializePieces(pieces);
	board.pieces = pieces;
	return board;
}

void initializePieces(Piece *pieces){
	int i;
	//White pieces
	for(i=0;i<16;i++){
		pieces[i].Color = white;
		pieces[i].InBoard = 1;
	}
	//Pawns
	char currentFile = 'a';
	for(i=0;i<8;i++){
		pieces[i].Type = pawn;
		pieces[i].File = currentFile;
		currentFile += 1;
		pieces[i].Rank = 2;
	}
	//Other pieces
	for(i=8;i<16;i++){
		pieces[i].Rank = 1;
	}
	//knights
	pieces[8].Type = knight;
	pieces[8].File = 'b';
	pieces[9].Type = knight;
	pieces[9].File = 'g';
	//bishops
	pieces[10].Type = bishop;
	pieces[10].File = 'c';
	pieces[11].Type = bishop;
	pieces[11].File = 'f';
	//rooks
	pieces[12].Type = rook;
	pieces[12].File = 'a';
	pieces[13].Type = rook;
	pieces[13].File = 'h';
	//queen
	pieces[14].Type = queen;
	pieces[14].File = 'd';
	//king
	pieces[15].Type = king;
	pieces[15].File = 'e';
	
	//Black pieces
	for(i=16;i<32;i++){
		pieces[i].Color = black;
		pieces[i].InBoard = 1;
	}
	//Pawns
	currentFile = 'a';
	for(i=16;i<24;i++){
		pieces[i].Type = pawn;
		pieces[i].File = currentFile;
		currentFile += 1;
		pieces[i].Rank = 7;
	}
	//Other pieces
	for(i=24;i<32;i++){
		pieces[i].Rank = 8;
	}
	//knights
	pieces[24].Type = knight;
	pieces[24].File = 'b';
	pieces[25].Type = knight;
	pieces[25].File = 'g';
	//bishops
	pieces[26].Type = bishop;
	pieces[26].File = 'c';
	pieces[27].Type = bishop;
	pieces[27].File = 'f';
	//rooks
	pieces[28].Type = rook;
	pieces[28].File = 'a';
	pieces[29].Type = rook;
	pieces[29].File = 'h';
	//queen
	pieces[30].Type = queen;
	pieces[30].File = 'd';
	//king
	pieces[31].Type = king;
	pieces[31].File = 'e';

	return;
}

int isGameOver(Board board){
	return 0;
}

int getWinner(Board board){
	return 0;
}

int isCellOccupiable(Board board, Color color, char file, int rank){
	int i;
	for(i=0;i<32;i++){
		if(board.pieces[i].File == file && board.pieces[i].Rank == rank && board.pieces[i].Color == color){
			return 0;
		}
	}
	return 1;
}

int getPieceIndexByType(Board board, Color color, Type type){
	int i;
	for(i=0;i<32;i++){
		if(board.pieces[i].Type == type && board.pieces[i].Color == color){
			return i;
		}
	}
}

int isValidCell(char file, int rank){
	if(file>='a' && file<='h' && rank>=1 && rank <=8)
		return 1;
	return 0;
}

int isValidMove(Board board, char oldFile, int oldRank, char newFile, int newRank){
}
