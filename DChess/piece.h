#pragma once
#include <vector>
#include "gameObject.h"
#include <iostream>
class Piece :public gameObject {
public:
	Piece(int, bool, int, const char*, Pos);
	Piece(int type, bool color, int pos, const char* texname, Pos pos_, int w, int h);
	~Piece();

	// 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn
	void Move(const int);
	void InitPiece(int, bool, int);
	void Touch() { touch++; }
//	void Draw() override;
	int GetPos() { return pos; }
	bool GetColor() { return color; }
	bool IsUntouched() { std::cout << touch << "\n"; return (touch == 0); }
	int GetType() { return type; }
	//bool moveLegal(int pos);

private:
	
	int type;
	int pos;
	
	int touch = 0;
	bool color;
};

