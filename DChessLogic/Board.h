#pragma once
#include <vector>
class Board{
public:
	
		class Piece {
	public:
		Piece(int , bool , int);
		~Piece();
	
		// 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn
		void Move(const int );
		void InitPiece(int , bool , int );
		int GetPos() { return pos; }
		bool GetColor() { return color; }
		int GetType() { return type; }

	private:
		int type;
		int pos;
		bool color;
	};
	//Piece* GetBrdState(const int);

	void Init( const char* fen);
	void Draw();
	void Show();
	void Move(const char*);
	static int GetNumberPos(const char*);
	static const char* GetPosFromNumber(const int);
	static int getTypeFromLetter(const char c);
private:
	bool sideToMove;// 0 - black, 1 - white
	int semiClock;
	int fullClock;
	const int dim = 8;
	std::vector<Piece*> pieces_; // contains ehm... uwu...  ><
	Piece* BoardState[64]; // contains "references" to pieces, refers to NULL when cell is not occupied
};


