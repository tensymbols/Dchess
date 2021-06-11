#include "Board.h"
#include <iostream>
#include <string>



Board::Board(const char* texfile, SDL_Renderer*rnd, Pos pos_, SDL_Color wf, SDL_Color bf, int w=0, int h=0) : gameObject(texfile,rnd,pos_,w, h), bfield(bf), wfield(wf)
{
	for (size_t i = 0; i < dim * dim; i++)
		BoardState[i] = NULL;
	fullClock = 0;
	semiClock = 0;
	sideToMove = 1;
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			int index = j + i * 8;
			squares[index].w = dim,
			squares[index].h = dim;
			squares[index].x = this->getPos().x + j * dim;
			squares[index].y = this->getPos().y + i * dim;
//			std::cout << index << " " << squares[index].w << " " << squares[index].h << " " << squares[index].x << " " << squares[index].y<< "\n";
		}
	}
}
Board::Board(const char* texfile, SDL_Renderer* rnd, Pos pos_, SDL_Color wf, SDL_Color bf) : gameObject(texfile, rnd, pos_), bfield(bf), wfield(wf)
{
	for (size_t i = 0; i < dim * dim; i++)
 	BoardState[i] = NULL;
	fullClock = 0;
	semiClock = 0;
	sideToMove = 1;
	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			int index = j + i * 8;
			squares[index].w = dim,
			squares[index].h = dim;
			squares[index].x = this->getPos().x + j * dim;
			squares[index].y = this->getPos().y + i * dim;
			//			std::cout << index << " " << squares[index].w << " " << squares[index].h << " " << squares[index].x << " " << squares[index].y<< "\n";
		}
	}
}


void Board::Init(const char* fen)
{
	//WHITE 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn 
	//BLACK 6 - rook, 7 - king, 8 - queen, 9 - knight, 10 - bishop, 11 - pawn 


	
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
		
			std::string sNum = std::to_string(ttype+1);
			 char tempTexName[] = { "textures\\pieces0_" };
			strcat(tempTexName, sNum.c_str());
			strcat(tempTexName, ".png");

			std::string S = tempTexName;
			std::cout << S;
			pieces_.push_back(new Piece(ttype, tcolor, pos, tempTexName, this->getRnd(), {0,0},dim,dim));
			BoardState[pos] = pieces_[pieces_.size() - 1];
			pos++;
		}
		k++;

	}



}

int Board::getTypeFromLetter(const char c) {
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
		int i = 7 - (coord[1] - 48 - 1);
		//std::cout << i << " " << j;  //i*dim+j = pos; 
		return (i * 8 + j);

	}
}

const char* Board::GetPosFromNumber(const int pos)
{
	char pos_[2];
	int num = pos / 8 + 1;
	char letter = 64 - (pos / 8) + 97;
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
		throw;
	}
	//	std::cout << pos1_ << " " << pos2_;
		// {
}

void Board::Draw() {

	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			int index = j + i * 8;
			if ((i + j) % 2)
			{
				SDL_SetRenderDrawColor(this->getRnd(), bfield.r, bfield.g, bfield.b, 255);
				std::cout << "blek ";
			}
			else
			{
				SDL_SetRenderDrawColor(this->getRnd(), wfield.r, wfield.g, wfield.b, 255);
				std::cout << "whit ";
			}
			std::cout << index << " " << squares[index].w << " " << squares[index].h << " " << squares[index].x << " " << squares[index].y << "\n";
			SDL_RenderFillRect(this->getRnd(), &squares[index]);
			SDL_RenderDrawRect(this->getRnd(), &squares[index]);
		}
	}
	for (size_t i = 0; i < pieces_.size(); i++)
	{
		pieces_[i]->Draw();
	//	SDL_RenderPresent(this->getRnd());
	}

}

void Board::Show() {

	for (size_t i = 0; i < 32; i++)
	{
		std::cout << pieces_[i]->GetPos() << " ";
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

