#pragma once
#include <vector>
#include "gameObject.h"

class Piece :public gameObject {
public:
	Piece(int, bool, int, const char*, SDL_Renderer*, Pos);
	~Piece();
	
	// 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn
	void Move(const int);
	void InitPiece(int, bool, int);
	void Draw() override;
	int GetPos() { return pos; }
	bool GetColor() { return color; }
	int GetType() { return type; }

private:
	int type;
	int pos;
	bool color;
};

