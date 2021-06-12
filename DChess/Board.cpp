#include "Board.h"
#include <iostream>
#include <string>



/*Board::Board(const char* texfile, Pos pos_, SDL_Color wf, SDL_Color bf, int dim, int w, int h) : gameObject(texfile,pos_,w, h), bfield(bf), wfield(wf), dim(dim)
{
	for (size_t i = 0; i < 64; i++) {
		BoardState[i] = NULL;
		marked[i] = 0;
	}
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
}*/
Board::Board(const char* texfile, Pos pos_, SDL_Color wf, SDL_Color bf, int dim) : gameObject(texfile,  pos_,dim*8,dim*8), bfield(bf), wfield(wf), dim(dim)
{
	holdPiece = NULL;
	for (size_t i = 0; i < 64; i++) { // 
		BoardState[i] = NULL;
		marked[i] = 0;
	}
	for (size_t i = 0; i < 8; i++) // squares color init
	{
		for (size_t j = 0; j < 8; j++)
		{
			int index = j + i * 8;
			if ((i + j) % 2)
				colSquares[index] = wf;
			else
				colSquares[index] = bf;
		}
	}
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
			std::string tempTexName ="textures\\pieces0_" ;
			tempTexName += sNum;
			tempTexName += ".png";

		//	std::cout << relPosition.x << " " << relPosition.y << "\n";
			pieces_.push_back(new Piece(ttype, tcolor, pos, tempTexName.c_str(),getRelPosition(pos),dim,dim));

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

void Board::changeColor(SDL_Color w, SDL_Color b)
{
	wfield = w;
	bfield = b;
}

int Board::getPosFromMouse(Pos pos)
{
	Pos brdPos = this->getPos();
	Pos relativePos;
	relativePos.x = pos.x - brdPos.x;
	relativePos.y = pos.y - brdPos.y;
	int i = relativePos.x / dim;
	int j = relativePos.y / dim;
	int pos_ = j * 8 + i;
	return pos_;
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

	pos_[0] = letter;
	pos_[1] = num + 48;
	return pos_;
}
Pos Board::GetCoordFromNumber(const int pos)
{

	int y = pos / 8;
	int x = pos-y*8;

	Pos temp = {x,y };
	return temp;
}

void Board::handleEvent(SDL_Event &e)
{
	switch (e.type) {
	case SDL_MOUSEMOTION:
		
		Pos mpos;
		mpos.x = e.motion.x;
		mpos.y = e.motion.y;
		
		if (isInside(mpos)) {
			if (holdPiece != NULL) {
				holdPiece->setPos({mpos.x-dim/2,mpos.y-dim/2});
			}

			unmark(prevMarked);
			int pos_ = getPosFromMouse(mpos);
		//	std::cout <<  pos_<<"\n";
			prevMarked = pos_;
			if (!marked[pos_]) mark(pos_);
		}
		else {
			unmark(prevMarked);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (e.button.button == SDL_BUTTON_LEFT) {
			int x, y;
			//std::cout << "pressed";
			SDL_GetMouseState(&x, &y);
			Pos mpos; mpos.x = x; mpos.y = y;
		
			if (isInside(mpos)) {
				int pos_ = getPosFromMouse(mpos);
				if (BoardState[pos_] != NULL) {
					holdPiece = BoardState[pos_];
				//	std::cout <<  BoardState[pos_]->GetPos()<< " ";
				}
			}

		}
		else if (e.button.button == SDL_BUTTON_RIGHT) {

		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (e.button.button == SDL_BUTTON_LEFT) {
			int x, y;

			SDL_GetMouseState(&x, &y);
			Pos mpos; mpos.x = x; mpos.y = y;

			if (isInside(mpos)) {
				int pos_ = getPosFromMouse(mpos);
				if (holdPiece!=NULL) {
				
					Move(holdPiece->GetPos(), pos_);
			
				}
			}
			if (holdPiece != NULL) holdPiece = NULL;

		}
		else if (e.button.button == SDL_BUTTON_RIGHT) {

		}		break;
	}
}

Pos Board::getRelPosition(int pos)
{
	Pos position = GetCoordFromNumber(pos);
	Pos relPosition = { position.x * dim + this->getPos().x, position.y * dim + this->getPos().y };
	return relPosition;
}


void Board::Move(const char* coord) {

	char pos1[2] = { coord[0], coord[1] };
	//std::cout << pos1[0] << pos1[1] << " ";
	char pos2[2] = { coord[3], coord[4] };
	//	std::cout << pos2[0] << pos2[1] << "\n";
	try {
		int pos1_ = GetNumberPos(pos1);
		int pos2_ = GetNumberPos(pos2);
	//	std::cout << BoardState[pos1_] << " " << BoardState[pos2_];
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

void Board::Move(int pos1, int pos2)
{

	try {
		if (pos1 == pos2) {
			BoardState[pos1]->setPos(getRelPosition(pos2));
		}
		else {
			//	std::cout << BoardState[pos1_] << " " << BoardState[pos2_];
			if (!BoardState[pos1]) {
				std::cout << ("Illegal move\n");
			}
			else {
				BoardState[pos1]->Move(pos2);
				BoardState[pos2] = BoardState[pos1];

				BoardState[pos1]->setPos(getRelPosition(pos2));
				BoardState[pos1] = NULL;
			}
		}
	}
	catch (...) {
		throw;
	}
}

void Board::mark(const int index)
{
	SDL_Color temp;
	temp.r = (colSquares[index].r + 255)/2;
	temp.g = colSquares[index].g/2;
	temp.b = colSquares[index].b/2; temp.a = 255;
	colSquares[index] = temp;
	marked[index] = 1;
}
void Board::unmark(const int index)
{
	Pos temp=GetCoordFromNumber(index);
	if ((temp.x + temp.y) % 2)
		colSquares[index] = wfield;
	else
		colSquares[index] = bfield;
	marked[index] = 0;
}

void Board::Draw() {

	for (size_t i = 0; i < 8; i++)
	{
		for (size_t j = 0; j < 8; j++)
		{
			int index = j + i * 8;
			SDL_SetRenderDrawColor(gameObject::rnd,colSquares[index].r, colSquares[index].g, colSquares[index].b, 255);
			//std::cout << index << " " << squares[index].w << " " << squares[index].h << " " << squares[index].x << " " << squares[index].y << "\n";
			SDL_RenderFillRect(gameObject::rnd, &squares[index]);
			SDL_RenderDrawRect(gameObject::rnd, &squares[index]);
		}
	}
	for (size_t i = 0; i < 64; i++)
	{
	//	std::cout << pieces_[i]->GetPos()<< " ";
		if (BoardState[i]!=NULL) {
			BoardState[i]->Draw();
				//BoardState[i]->Draw({ position.x * dim+this->getPos().x,position.y * dim+this->getPos().y });
		}

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

