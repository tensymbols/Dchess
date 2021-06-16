#pragma once
#include <vector>
#include "gameObject.h"

class Piece :public gameObject {
public:
	Piece(int, bool, int, const char*,  Pos);
	Piece(int type, bool color, int pos, const char* texname, Pos pos_, int w, int h);
	~Piece();
	
	// 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn
	void Move(const int);
	void InitPiece(int, bool, int);
//	void Draw() override;
	int GetPos() { return pos; }
	bool GetColor() { return color; }
	int GetType() { return type; }
	bool moveLegal(int pos);

private:
	int type;
	int pos;
	
	bool color;
};

