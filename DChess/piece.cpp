#include "piece.h"

Piece::Piece(int type, bool color, int pos, const char* texname, SDL_Renderer*rnd, Pos pos_) : gameObject(texname,rnd,pos_)
{
}
Piece::Piece(int type, bool color, int pos, const char* texname, SDL_Renderer* rnd, Pos pos_, int w, int h) : gameObject(texname, rnd, pos_, w,h)
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
