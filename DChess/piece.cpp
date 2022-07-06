#include "piece.h"

Piece::Piece(int type, bool color, int pos, const char* texname, Pos pos_) :
	gameObject(texname, pos_), type_(type), boardpos_(pos), color_(color)
{
}

Piece::Piece(int type, bool color, int pos, const char* texname,
	Pos pos_, int w, int h, std::vector<Pos> deltas, int depth) :
	gameObject(texname, pos_, w, h),
	type_(type), boardpos_(pos), color_(color), deltas_(deltas), depth_(depth)
{
}



/*void Piece::Draw() {

}*/


void Piece::InitPiece(int type, bool color, int pos)
{
	this->type_ = type;
	this->color_ = color;
	this->boardpos_ = pos;
}

void Piece::addMove(int pos)
{
	moves_.push_back(pos);
}

void Piece::addMoves(std::vector<int> moves)
{
	moves_.insert(moves_.end(), moves.begin(), moves.end());
}

bool Piece::isMoveA(int pos)
{
	std::vector<int>::iterator it;
	it = std::find(moves_.begin(), moves_.end(), pos);
	return it != moves_.end();
}
bool Piece::hasDelta(Pos delta) {
	std::vector<Pos>::iterator it;
	it = std::find(deltas_.begin(), deltas_.end(), delta);
	return it != deltas_.end();
}



void Piece::clearMoves() {
	moves_.clear();
}

/*void Piece::copy(Piece* p)
{
	type = p->GetType();
	color = p->GetColor();
	pos = p->GetPos();
//	deltas           depth
}*/

void Piece::clear()
{
}


void Piece::Move(const int pos) {
	this->boardpos_ = pos;

}
