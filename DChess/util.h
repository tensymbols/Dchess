#include "pos.h"
#include "piece.h"
#include <iostream>
#include <vector>
class util {
public:
	util(Pos brd_pos, int sqr_dim, int brd_dim) :
		brd_pos_(brd_pos), sqr_dim_(sqr_dim), brd_dim_(brd_dim)
	{
	}

	Pos getAbsPosition(int rpos)
	{
		Pos position = getCoordFromNumber(rpos);
		Pos AbsPosition = { position.x * sqr_dim_ + brd_pos_.x, position.y * sqr_dim_ + brd_pos_.y };
		return AbsPosition;
	}
	int getPosFromMouse(Pos pos)
	{
		Pos AbsativePos;
		AbsativePos.x = pos.x - brd_pos_.x;
		AbsativePos.y = pos.y - brd_pos_.y;
		int i = AbsativePos.x / sqr_dim_;
		int j = AbsativePos.y / sqr_dim_;
		int pos_ = j * brd_dim_ + i;
		return pos_;
	}


	Pos getCoordFromNumber(const int pos)
	{

		int y = pos / brd_dim_;
		int x = pos - y * brd_dim_;

		Pos temp = { x,y };
		return temp;
	}

	int getNumberFromCoord(Pos pos)
	{

		return (pos.y * brd_dim_ + pos.x);
	}



	std::vector<Pos> deltasFromType(int type) {
		int ttype = type % 6;
		std::vector<Pos> deltas;
		deltas.clear();
		switch (ttype) {
			// 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn 
		case 0: {
			deltas = { {1, 0},{-1,0},{ 0,1}, {0,-1} }; // +
		}
			  break;
		case 1: {
			deltas = { {1, 0},{-1,0},{ 0,1}, {0,-1} ,{ -1, -1 }, { 1,-1 },{ -1,1 },{ 1,1 } }; // +
		}
			  break;
		case 2: {
			deltas = { {1, 0},{-1,0},{ 0,1}, {0,-1} ,{ -1, -1 }, { 1,-1 },{ -1,1 },{ 1,1 } }; // +
		}
			  break;
		case 3: {
			deltas = { {-2, 1},{2,1},{ -1,2}, {1,2} ,{ -2, -1 }, { 2,-1 },{ -1,-2 },{1,-2 } };
			break;
		}
		case 4: {
			deltas = { { -1, -1 }, { 1,-1 },{ -1,1 },{ 1,1 } };
			break;
		}
		case 5:
		{
			if (type != ttype) {
				deltas = { { -1, 1 }, { 1, 1 } };
			}
			else {
				deltas = { { -1, -1 }, { 1, -1 } };
			}
			break;
		}
		}
		return deltas;
	}
	int depthFromType(int type) {
		// 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn 

		int ttype = type % 6;
		switch (ttype) {
		case 0:
			return -1; //inf
		case 1:
			return 1;
		case 2:
			return -1;
		case 3:
			return 1;
		case 4:
			return -1;
		case 5:
			return 1;
		default:
			return 0;
		}
	}
	int getTypeFromLetter(const char c) {
		int ttype = -1;
		switch (c) {
		case 'R':
			ttype = 0;
			break;
		case 'N':
			ttype = 3;
			break;
		case 'B':
			ttype = 4;
			break;
		case 'Q':
			ttype = 2;
			break;
		case 'K':
			ttype = 1;
			break;
		case 'P':
			ttype = 5;
			break;
		case 'r':
			ttype = 6;
			break;
		case 'n':
			ttype = 9;
			break;
		case 'b':
			ttype = 10;
			break;
		case 'q':
			ttype = 8;
			break;
		case 'k':
			ttype = 7;
			break;
		case 'p':
			ttype = 11;
			break;
		}
		return ttype;
	}

	void displayIntVector(std::vector<int>& v) {

		for (size_t i = 0; i < v.size(); i++)
		{

			std::cout << v[i] << " ";
		}
		std::cout << "\n";
	}
	bool isInVector(std::vector<int>& v, int el) {
		std::vector<int>::iterator it;
		it = std::find(v.begin(), v.end(), el);
		return it != v.end();
	}
	std::vector<int> getIntersection(std::vector<int>& v1, std::vector<int>& v2) {
		std::vector<int>::iterator it;
		std::vector<int> result;
		for (size_t i = 0; i < v1.size(); i++)
		{
			if (isInVector(v2, v1[i]))
				result.push_back(v1[i]);
		}
		return result;
	}

	bool isPosLegal(int pos) {
		return pos >= 0 && pos < brd_dim_* brd_dim_;
	}
	bool sameSide(Piece* p1, Piece* p2)
	{
		return p1 != NULL && p2 != NULL
			&& p1->getColor() == p2->getColor();
	}
private:
	Pos brd_pos_;
	int sqr_dim_;
	int brd_dim_;
};