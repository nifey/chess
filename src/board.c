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
	int i, j;
	Piece *attacker = NULL, *victim = NULL;
	for(i=0;i<32;i++){
		if(board.pieces[i].File == oldFile && board.pieces[i].Rank == oldRank){
			attacker = board.pieces + i;
			continue;
		}
		if(board.pieces[i].File == newFile && board.pieces[i].Rank == newRank){
			victim = board.pieces + i;
			continue;
		}
	}
	if(attacker == NULL)
		return 0;
	if(attacker->Color != board.Turn || (victim != NULL && attacker->Color == victim->Color)){
		return 0;
	}
	int rankDiff, fileDiff, rankInc, fileInc, k;
	switch(attacker->Type){
		case pawn:
			if(victim==NULL && oldFile == newFile){
				if(attacker->Color == white && newRank == oldRank + 1){
					return 1;
				} else if (attacker->Color == black && newRank == oldRank - 1){
					return 1;
				}	
				if(attacker->Color == white && oldRank == 2 && newRank == 4){
					for(i=0;i<32;i++){
						if(board.pieces[i].File == oldFile && board.pieces[i].Rank == 3){
							return 0;
						}
					}
					return 1;
				} else if (attacker->Color == black && oldRank == 7 && newRank==5){
					for(i=0;i<32;i++){
						if(board.pieces[i].File == oldFile && board.pieces[i].Rank == 6){
							return 0;
						}
					}
					return 1;
				}
			} else if(victim != NULL && (newFile == oldFile-1 || newFile == oldFile+1)){
				if(attacker->Color == white && newRank == oldRank + 1){
					return 1;
				} else if (attacker->Color == black && newRank == oldRank - 1){
					return 1;
				}
			}
			//TODO Add rules for En Passant and Pawn Promotion
			return 0;
			break;
		case knight:
			rankDiff = (oldRank>newRank)? (oldRank-newRank): (newRank - oldRank);
			fileDiff = (oldFile>newFile)? (oldFile-newFile): (newFile - oldFile);
			if((rankDiff == 1 && fileDiff == 2)||(rankDiff == 2 && fileDiff == 1)){
				return 1;
			}
			return 0;
			break;
		case bishop:
			rankDiff = (oldRank>newRank)? (oldRank-newRank): (newRank - oldRank);
			fileDiff = (oldFile>newFile)? (oldFile-newFile): (newFile - oldFile);
			if(rankDiff != fileDiff){
				return 0;
			}
			rankInc = (oldRank>newRank)? -1: 1;
			fileInc = (oldFile>newFile)? -1: 1;
			for(i=oldRank+rankInc,j=oldFile+fileInc;i!=newRank&&j!=newFile;i+=rankInc,j+=fileInc){
				for(k=0;k<32;k++){
					if(board.pieces[k].File == j && board.pieces[k].Rank == i)
						return 0;
				}
			}
			return 1;
			break;
		case rook:
			rankDiff = (oldRank>newRank)? (oldRank-newRank): (newRank - oldRank);
			fileDiff = (oldFile>newFile)? (oldFile-newFile): (newFile - oldFile);
			if(rankDiff != 0 && fileDiff!=0){
				return 0;
			}
			rankInc = (rankDiff==0)? 0: 1;
			fileInc = (fileDiff==0)? 0: 1;
			for(i=oldRank+rankInc,j=oldFile+fileInc;i!=newRank&&j!=newFile;i+=rankInc,j+=fileInc){
				for(k=0;k<32;k++){
					if(board.pieces[k].File == j && board.pieces[k].Rank == i)
						return 0;
				}
			}
			return 1;
			break;
		case queen:
			rankDiff = (oldRank>newRank)? (oldRank-newRank): (newRank - oldRank);
			fileDiff = (oldFile>newFile)? (oldFile-newFile): (newFile - oldFile);
			if(rankDiff == 0 || fileDiff==0){
				rankInc = (rankDiff==0)? 0: 1;
				fileInc = (fileDiff==0)? 0: 1;
				for(i=oldRank+rankInc,j=oldFile+fileInc;i!=newRank&&j!=newFile;i+=rankInc,j+=fileInc){
					for(k=0;k<32;k++){
						if(board.pieces[k].File == j && board.pieces[k].Rank == i)
							return 0;
					}
				}
				return 1;
			}
			if(rankDiff == fileDiff){
				rankInc = (oldRank>newRank)? -1: 1;
				fileInc = (oldFile>newFile)? -1: 1;
				for(i=oldRank+rankInc,j=oldFile+fileInc;i!=newRank&&j!=newFile;i+=rankInc,j+=fileInc){
					for(k=0;k<32;k++){
						if(board.pieces[k].File == j && board.pieces[k].Rank == i)
							return 0;
					}
				}
				return 1;
			}
			return 0;
			break;
		case king:
			rankDiff = (oldRank>newRank)? (oldRank-newRank): (newRank - oldRank);
			fileDiff = (oldFile>newFile)? (oldFile-newFile): (newFile - oldFile);
			if(rankDiff <= 1 && fileDiff <= 1){
				return 1;
			}
			//TODO add rule for castling
			return 0;
			break;
	}
}

void move(Board board, char oldFile, int oldRank, char newFile, int newRank){
	int i;
	Piece *attacker = NULL, *victim = NULL;
	for(i=0;i<32;i++){
		if(board.pieces[i].File == oldFile && board.pieces[i].Rank == oldRank){
			attacker = &board.pieces[i];
		}
		if(board.pieces[i].File == newFile && board.pieces[i].Rank == newRank){
			victim = &board.pieces[i];
		}
	}
	if(victim != NULL){
		victim->InBoard=0;
		victim->Rank=9;
		victim->File='z';
	}
	attacker->File = newFile;
	attacker->Rank = newRank;
}
