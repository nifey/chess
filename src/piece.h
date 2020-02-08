
enum color { black, white };
typedef enum color Color;

enum type { pawn, bishop, knight, rook, queen, king};
typedef enum type Type;

struct Piece{
	Color Color;
	Type Type;
	int InBoard;
	char File;
	int Rank;
};
typedef struct Piece Piece;

struct Piece createPiece(Color c, Type t, char file, int rank);

int hasDifferentColor(Piece p1, Piece p2);
