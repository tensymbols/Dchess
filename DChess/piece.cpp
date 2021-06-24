#include "piece.h"

Piece::Piece(int type, bool color, int pos, const char* texname, Pos pos_) :
	gameObject(texname, pos_), type(type), pos(pos), color(color)
{
}
Piece::Piece(int type, bool color, int pos, const char* texname, Pos pos_, int w, int h) : 
	gameObject(texname, pos_, w,h), 
	type(type), pos(pos), color(color)
{
}

Piece::~Piece() {
	//delete this;
}

/*void Piece::Draw() {

}*/


void Piece::InitPiece(int type, bool color, int pos)
{
	this->type = type;
	this->color = color;
	this->pos = pos;
}

void Piece::addMove(int pos)
{
	aMoves.push_back(pos);
}

bool Piece::isMoveA(int pos)
{
	std::vector<int>::iterator it;
	it = std::find(aMoves.begin(), aMoves.end(), pos);
	return it != aMoves.end();
}

std::vector<int> Piece::getMoves()
{
	return aMoves;
}

void Piece::clearMoves() {
	aMoves.clear();
}

void Piece::Move(const int pos) {
	this->pos = pos;

}
