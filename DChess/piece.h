#pragma once
#include <vector>
#include "gameObject.h"
#include <iostream>
class Piece :public gameObject {
public:
	Piece(int, bool, int, const char*, Pos);
	Piece(int type, bool color, int pos, const char* texname, Pos pos_, int w, int h, std::vector<Pos> deltas, int depth);
	~Piece();

	// 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn
	void Move(const int);
	void InitPiece(int, bool, int);
	void Touch() { touch++; }

	void addMove(int pos); // add move to available moves
	void addMoves(std::vector<int> moves);

	bool isMoveA(int pos); // is move available
	bool hasDelta(Pos delta);
	std::vector<int> getMoves();
	std::vector<Pos> getDeltas();
	int getDepth();
	void clearMoves();
	//void copy(Piece*);
	void clear();
	//	void Draw() override;
	int GetPos() { return pos; }
	bool GetColor() { return color; }
	bool IsUntouched() { return (touch == 0); }
	int GetType() { return type; }
	//bool moveLegal(int pos);

private:

	int type;
	int pos;
	std::vector<int> moves_;

	std::vector<Pos> deltas;
	int depth = 0;

	int touch = 0;
	bool color;
};

