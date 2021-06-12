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
	delete this;
}

/*void Piece::Draw() {

}*/


void Piece::InitPiece(int type, bool color, int pos)
{
	this->type = type;
	this->color = color;
	this->pos = pos;
}
void Piece::Move(const int pos) {
	this->pos = pos;

}
