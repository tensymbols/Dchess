#pragma once

#include <vector>
#include "gameObject.h"
#include <iostream>

class Piece :public gameObject {
public:
	Piece(int, bool, int, const char*, Pos);
	Piece(int type, bool color, int pos, const char* texname, Pos pos_, int w, int h, std::vector<Pos> deltas, int depth);


	// 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn
	void Move(const int);
	void InitPiece(int, bool, int);
	void Touch() { touch_++; }

	

	void addMove(int pos); // add move to available moves
	void addMoves(std::vector<int> moves);

	bool isMoveA(int pos); // is move available
	bool hasDelta(Pos delta);
	
	
	void clearMoves();
	//void copy(Piece*);
	void clear();
	//	void Draw() override;
	void setType(int type) { type_ = type; }
	void setDeltas(std::vector<Pos> deltas) { deltas_ = deltas; }
	void setDepth(int depth) { depth_ = depth; }

	int getDepth() { return depth_; }
	int getBrdPos() { return boardpos_; }
	bool getColor() { return color_; }
	int getType() { return type_; }
	std::vector<int> getMoves() { return moves_; }
	std::vector<Pos> getDeltas() { return deltas_; }

	bool isUntouched() { return (touch_ == 0); }


	//bool moveLegal(int pos);

private:

	int type_;
	int boardpos_;
	bool color_;
	std::vector<int> moves_;

	std::vector<Pos> deltas_;
	int depth_ = 0;

	int touch_ = 0;
	
};

