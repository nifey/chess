#include "piece.h"

Piece createPiece(Color c, Type t, char file, int rank){
	Piece p;
	p.Color = c;
	p.Type = t;
	p.File = file;
	p.Rank = rank;
	p.InBoard = 1;
	return p;
}

int hasDifferentColor(Piece p1, Piece p2){
	return p1.Color != p2.Color;
}
