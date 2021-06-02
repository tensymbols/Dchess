#include "Board.h"
#include <windows.h>
#include <iostream>

Board::Piece::~Piece() {
	delete this;
}
Board::Piece::Piece(int type, bool color, int pos):type(type), color(color), pos(pos) {

}


void Board::Piece::InitPiece(int type, bool color, int pos)
{
	this->type = type;
	this->color = color;
	this->pos = pos;
}

int Board::getTypeFromLetter(const char c) {
	int ttype=-1;
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

void Board::Init(const char* fen)
{
	//WHITE 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn 
	//BLACK 6 - rook, 7 - king, 8 - queen, 9 - knight, 10 - bishop, 11 - pawn 


	for (size_t i = 0; i < 64; i++)
		BoardState[i] = NULL;
	 // fen reading;
	int pos = 0;
	int k = 0;
	while (fen[k] != ' ') 
	{
		int ttype = -1; bool tcolor = 0;
		if (fen[k] > 47 && fen[k] < 58)
		{
			pos += (fen[k] - 48);
		}
		else if (fen[k] > 64 && fen[k] < 91 ||
				 fen[k] > 97 && fen[k] < 123)
		{
			
			ttype = getTypeFromLetter(fen[k]);
			tcolor = (ttype < 6);
			pieces_.push_back(new Piece(ttype, tcolor, pos));
			BoardState[pos] = pieces_[pieces_.size()-1];
			pos++;
		}
		k++;
	
	}
                     
}

int Board::GetNumberPos(const char* coord)
{
	/*char k;
	k = 0;
	while (coord[k]!='\0')
		k++;*/

	bool wrongInput =
		((coord[0] < 97 || coord[0] > 104) ||
		 (coord[1] < 48 || coord[1]>56));
	if (wrongInput) {
		throw std::string("Incorrect input");
		//return -1;
	}
	else {
		int j = (coord[0] - 97);
		int i = 7-(coord[1] - 48-1);
		//std::cout << i << " " << j;  //i*dim+j = pos; 
		return (i*8+j);
	
	}
}

const char* Board::GetPosFromNumber(const int pos)
{
	char pos_[2];
	int num = pos / 8 + 1;
	char letter = 64-(pos/8)+97;
	return nullptr;
	pos_[0] = letter; 
	pos_[1] = num + 48;
	return pos_;
}


void Board::Move(const char* coord) {

	char pos1[2] = { coord[0], coord[1] };
	//std::cout << pos1[0] << pos1[1] << " ";
	char pos2[2] = { coord[3], coord[4] };
//	std::cout << pos2[0] << pos2[1] << "\n";
	try {
		int pos1_ = GetNumberPos(pos1);
		int pos2_ = GetNumberPos(pos2);
		std::cout << BoardState[pos1_] << " " << BoardState[pos2_];
		if (!BoardState[pos1_] || pos1_ == pos2_) {
			std::cout << ("Illegal move\n"); 
		}
		else {
			BoardState[pos1_]->Move(pos2_);
			BoardState[pos2_] = BoardState[pos1_];
			BoardState[pos1_] = NULL;
		}
	}
	catch (...) {
		throw ;
	}

//	std::cout << pos1_ << " " << pos2_;
	// {
	

}
void Board::Piece::Move(const int pos) {
	this->pos = pos;
}

void Board::Draw() {
	HANDLE handleStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int pos = 0;
	for (size_t i = 0; i < dim; i++)
	{
		for (size_t j = 0; j < dim; j++)
		{
			char symbol=' ';
			pos = (dim * i) + j;
			//std::cout << pos;
			if (BoardState[pos]) {
				if ((i + j) % 2 == 0) {

					if (BoardState[pos]->GetColor() == 1) {
						SetConsoleTextAttribute(handleStdOut, 0x7F);
					}
					else {
						SetConsoleTextAttribute(handleStdOut, 0x70);
					}
				}
				else {
					if (BoardState[pos]->GetColor() == 1) {
						SetConsoleTextAttribute(handleStdOut, 0x8F);
					}
					else {
						SetConsoleTextAttribute(handleStdOut, 0x80);
					}
				}
				int type_ = BoardState[pos]->GetType();
				switch (type_) {
				case 0 :
					symbol = 'R';
					break;
				case 1 :
					symbol = 'K';
					break;
				case 2 :
					symbol = 'Q';
					break;
				case 3:
					symbol = 'N';
					break;
				case 4:
					symbol = 'B';
					break;
				case 5:
					symbol = 'o';
					break;
				case 6:
					symbol = 'R';
					break;
				case 7:
					symbol = 'K';
					break;
				case 8:
					symbol = 'Q';
					break;
				case 9:
					symbol = 'N';
					break;
				case 10:
					symbol = 'B';
					break;
				case 11:
					symbol = 'o';
					break;
				}
			}
			else if ((i + j) % 2 == 0)
			{
				SetConsoleTextAttribute(handleStdOut, 0x7F);
			}
			else 
			{
				SetConsoleTextAttribute(handleStdOut, 0x8F);
			}
			std::cout << " "<<symbol<<" ";
		}
		std::cout << std::endl;
	}
	SetConsoleTextAttribute(handleStdOut, 0x0F);
}

void Board::Show() {

	for (size_t i = 0; i < 32; i++)
	{
		std::cout << pieces_[i]->GetPos()<< " ";
	}
	bool tcolor;
	int tpos, ttype; 
	for (size_t i = 0; i < 64; i++)
	{
		if (BoardState[i])
		{
			tcolor = BoardState[i]->GetColor();
			tpos = BoardState[i]->GetPos();
			ttype = BoardState[i]->GetType();
			//std::cout << tcolor;
			switch (tcolor) {
			case 0:
				std::cout << "black ";
				break;
			case 1:
				std::cout << "white ";
				break;
			}

			std::cout << tpos << " ";
		}
		else std::cout << "mt";
	}
}

