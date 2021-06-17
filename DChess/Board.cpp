#include "Board.h"
#include <iostream>
#include <string>
	


/*Board::Board(const char* texfile, Pos pos_, SDL_Color wf, SDL_Color bf, int sqr_dim, int w, int h) : gameObject(texfile,pos_,w, h), bfield(bf), wfield(wf), sqr_dim(sqr_dim)
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
			squares[index].w = sqr_dim,
			squares[index].h = sqr_dim;
			squares[index].x = this->getPos().x + j * sqr_dim;
			squares[index].y = this->getPos().y + i * sqr_dim;
//			std::cout << index << " " << squares[index].w << " " << squares[index].h << " " << squares[index].x << " " << squares[index].y<< "\n";
		}
	}
}*/
Board::Board(const char* texfile, Pos pos_, SDL_Color wf, SDL_Color bf, int sqr_dim) : gameObject(texfile,  pos_,sqr_dim*8,sqr_dim*8), bfield(bf), wfield(wf), sqr_dim(sqr_dim)
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
			squares[index].w = sqr_dim,
			squares[index].h = sqr_dim;
			squares[index].x = this->getPos().x + j * sqr_dim;
			squares[index].y = this->getPos().y + i * sqr_dim;
		}
	}
}


void Board::Init(const char* fen)
{
	//WHITE 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn 
	//BLACK 6 - rook, 7 - king, 8 - queen, 9 - knight, 10 - bishop, 11 - pawn 


	// fen reading;
	sideToMove = 1;
	semiClock = 0;
	fullClock = 0;
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

		//	std::cout << AbsPosition.x << " " << AbsPosition.y << "\n";
			pieces_.push_back(new Piece(ttype, tcolor, pos, tempTexName.c_str(),getAbsPosition(pos),sqr_dim,sqr_dim));

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
	Pos AbsativePos;
	AbsativePos.x = pos.x - brdPos.x;
	AbsativePos.y = pos.y - brdPos.y;
	int i = AbsativePos.x / sqr_dim;
	int j = AbsativePos.y / sqr_dim;
	int pos_ = j * 8 + i;
	return pos_;
}

int Board::getNumberPos(const char* coord)
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
		//std::cout << i << " " << j;  //i*sqr_dim+j = pos; 
		return (i * 8 + j);

	}
}

const char* Board::getPosFromNumber(const int pos)
{
	char pos_[2];
	int num = pos / 8 + 1;
	char letter = 64 - (pos / 8) + 97;

	pos_[0] = letter;
	pos_[1] = num + 48;
	return pos_;
}
Pos Board::getCoordFromNumber(const int pos)
{

	int y = pos / 8;
	int x = pos-y*8;

	Pos temp = {x,y };
	return temp;
}

int Board::getNumberFromCoord(Pos pos)
{

	return (pos.y*brd_dim+pos.x);
}

void Board::keepInsde(Pos &pos)
{
	Pos brdpos = this->getPos();
	int x_right = brdpos.x + sqr_dim * 8;
	int y_down = brdpos.y + sqr_dim * 8;
	int x_left = brdpos.x;
	int y_up = brdpos.y;
	if (pos.x > x_right) pos.x = x_right;
	if (pos.x < x_left) pos.x = x_left;
	if (pos.y > y_down) pos.y = y_down;
	if (pos.y < y_up) pos.y = y_up;
}

void Board::handleEvent(SDL_Event &e)
{

	switch (e.type) {
	case SDL_MOUSEMOTION:  // when mouse is moving
		
		Pos mpos;
		mpos.x = e.motion.x;
		mpos.y = e.motion.y;
		
		if (isInside(mpos)) {
			if (holdPiece != NULL) {

				holdPiece->setPos({mpos.x-sqr_dim/2,mpos.y-sqr_dim/2}); // if there is a held piece it will drag it with mouse cursor
			}

			//unmark(prevMarked);
			int pos_ = getPosFromMouse(mpos);

			prevMarked = pos_;
			//if (!marked[pos_]) mark(pos_);
		}
		else {

			if (holdPiece != NULL) {
				keepInsde(mpos);
				holdPiece->setPos({ mpos.x - sqr_dim / 2,mpos.y - sqr_dim / 2 });
			}
			unmark(prevMarked);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		// when mouse button is pressed
		if (e.button.button == SDL_BUTTON_LEFT) { 
			
			if (LMB_STATE == 0) {
				
				LMB_STATE = true;
			//	std::cout << LMB_STATE << "\n";
				int x, y;
				SDL_GetMouseState(&x, &y);
				Pos mpos; mpos.x = x; mpos.y = y;

				if (isInside(mpos)) {
					int pos_ = getPosFromMouse(mpos);
					unmarkLegal();
					if (BoardState[pos_] != NULL) {
						holdPiece = BoardState[pos_]; // if mouse position is inside board and square where mouse is at is not empty holdpiece is initialized
						temp_moves = allLegal(holdPiece);
						drawLegal();
						


					}
				}
			}

		}
		else if (e.button.button == SDL_BUTTON_RIGHT) { 

		}
		break;
	case SDL_MOUSEBUTTONUP: // when mouse button is released
		if (e.button.button == SDL_BUTTON_LEFT) {
			if (LMB_STATE==1) {
				LMB_STATE = 0;
				int x, y;

			//	std::cout << LMB_STATE << "\n";
				SDL_GetMouseState(&x, &y);
				Pos mpos; mpos.x = x; mpos.y = y;


				if (holdPiece != NULL) {
					if (isInside(mpos)) {  // if mouse is inside board
						int pos_ = getPosFromMouse(mpos);


						if (isLegal(holdPiece, pos_)) { // if move is legal
							Move(holdPiece->GetPos(), pos_); // move piece to specified position
							sideToMove = !sideToMove;
							unmarkLegal();
						}
						else {
							Move(holdPiece->GetPos(), holdPiece->GetPos()); // if not legal then move piece back

						}
					}
					else {
						Move(holdPiece->GetPos(), holdPiece->GetPos()); // if mouse is outside the board bring held piece back

					}
				}
				holdPiece = NULL;
			}

		}
		else if (e.button.button == SDL_BUTTON_RIGHT) {

		}		break;
	}
}
bool Board::isLegal( Piece* p, int pos) {

	if (temp_moves.size() == 0) {
		std::cout << "No legal moves available\n";
		return false;

	}

	std::vector<int>::iterator it;
	it = std::find(temp_moves.begin(), temp_moves.end(), pos);

	return (it != temp_moves.end()); // if iterator reaches moves.end then there is no position we are trying to put our piece to among available legal moves

}
std::vector<int> Board::legal(std::vector<Pos>& deltas, int pos, int depth) { // part of available moves (for rook bishop and queen)

	Pos coord = Board::getCoordFromNumber(pos);
	std::vector<int> lmoves;
	Pos delta;
	for(size_t i=0; i<deltas.size();i++)
	{
		delta=deltas[i];
		coord += delta;

		for (size_t i = 0; i < depth && coord.x >= 0 && coord.x < brd_dim &&
			coord.y >= 0 && coord.y < brd_dim; i++)

		{
			int t_pos = coord.y * brd_dim + coord.x;
			if (BoardState[t_pos] == NULL) {
				lmoves.push_back(t_pos);
				//std::cout << "check2\n";
			}
			else {
				if (BoardState[t_pos]->GetColor() != sideToMove) lmoves.push_back(t_pos);
				break;
			}
			coord += delta;
		}
		coord = Board::getCoordFromNumber(pos);
	}
	return lmoves;
}

std::vector<int> Board::allLegal( Piece* p)
{

	//WHITE 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn 
	//BLACK 6 - rook, 7 - king, 8 - queen, 9 - knight, 10 - bishop, 11 - pawn 
	std::vector<int> moves;
	if (p->GetColor() != sideToMove) {
		if(sideToMove)
		std::cout << "Its  "<< " white's "<<" turn now\n";
		else std::cout << "Its  " << " black's " << " turn now\n";
		return moves;

	}

	/*if (BoardState[pos] != NULL && BoardState[pos]->GetColor() == p->GetColor())
	{
		std::cout << "Cant eat your own pieces\n";
		return moves;

	}*/
	int ttype = p->GetType();
	ttype %= 6;
	int currPos = p->GetPos();
	std::vector<int> legal_temp;
	std::vector<Pos> deltas;
	switch (ttype) {
	case 0: {
		deltas = { {1, 0},{-1,0},{ 0,1}, {0,-1} };
		legal_temp = legal(deltas, currPos, brd_dim);
		moves.insert(moves.end(), legal_temp.begin(), legal_temp.end());

	}
		  break;
	case 1: {
		deltas = { {1, 0},{-1,0},{ 0,1}, {0,-1} ,{ -1, -1 }, { 1,-1 },{ -1,1 },{ 1,1 } };
		legal_temp = legal(deltas, currPos, 1);
		moves.insert(moves.end(), legal_temp.begin(), legal_temp.end());
	}
		  break;
	case 2: {
		deltas = { {1, 0},{-1,0},{ 0,1}, {0,-1} ,{ -1, -1 }, { 1,-1 },{ -1,1 },{ 1,1 } };
		legal_temp = legal(deltas, currPos, 1);
		moves.insert(moves.end(), legal_temp.begin(), legal_temp.end());
	}
		  break;
	case 3: {
		deltas = { {-2, 1},{2,1},{ -1,2}, {1,2} ,{ -2, -1 }, { 2,-1 },{ -1,-2 },{1,-2 } };
		legal_temp = legal(deltas, currPos, 1);
		moves.insert(moves.end(), legal_temp.begin(), legal_temp.end());
		break;
	}
	case 4: {
		deltas = { { -1, -1 }, { 1,-1 },{ -1,1 },{ 1,1 } };
		legal_temp = legal(deltas, currPos, brd_dim);
		moves.insert(moves.end(), legal_temp.begin(), legal_temp.end());
		break;
	}
	case 5: {
		if (p->GetColor()==1) { //white pawn
			// manually adding legal moves to pawns bc its moves cant be described with legal() function
			int numPos = currPos - brd_dim - 1;
			if (BoardState[numPos] != NULL && BoardState[numPos]->GetColor() !=sideToMove) moves.push_back(numPos);

			numPos = currPos - brd_dim + 1;
			if (BoardState[numPos] != NULL && BoardState[numPos]->GetColor() != sideToMove) moves.push_back(numPos);

			numPos = currPos - brd_dim;
			if (numPos >= 0 && BoardState[numPos] == NULL) {
				moves.push_back(numPos);
				if (BoardState[currPos]->IsUntouched()) {
					numPos = currPos - 2 * brd_dim;
					if ( BoardState[numPos] == NULL) moves.push_back(numPos);
				}
			}

		} 
		else if (p->GetColor() == 0) { // black pawn
			int numPos = currPos + brd_dim - 1;
			if (BoardState[numPos] != NULL && BoardState[numPos]->GetColor() != sideToMove) moves.push_back(numPos);

			numPos = currPos + brd_dim + 1;
			if (BoardState[numPos] != NULL && BoardState[numPos]->GetColor() != sideToMove) moves.push_back(numPos);

			numPos = currPos + brd_dim;
			if (numPos >= 0 && BoardState[numPos] == NULL) {
				moves.push_back(numPos);
				if (BoardState[currPos]->IsUntouched()) {
					numPos = currPos + 2 * brd_dim;
					if (BoardState[numPos] == NULL) moves.push_back(numPos);
				}
			}
		}
		break;
		}
	}

	return moves;
}

Pos Board::getAbsPosition(int pos)
{
	Pos position = getCoordFromNumber(pos);
	Pos AbsPosition = { position.x * sqr_dim + this->getPos().x, position.y * sqr_dim + this->getPos().y };
	return AbsPosition;
}


void Board::Move(const char* coord) {

	char pos1[2] = { coord[0], coord[1] };
	//std::cout << pos1[0] << pos1[1] << " ";
	char pos2[2] = { coord[3], coord[4] };
	//	std::cout << pos2[0] << pos2[1] << "\n";
	try {
		int pos1_ = getNumberPos(pos1);
		int pos2_ = getNumberPos(pos2);
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
			BoardState[pos1]->setPos(getAbsPosition(pos2));
		}
		else {
			//	std::cout << BoardState[pos1_] << " " << BoardState[pos2_];
			if (BoardState[pos1]==NULL) {
				std::cout << ("Illegal move\n");
			}
			else {
				BoardState[pos1]->Move(pos2);
				//delete BoardState[pos2];

				BoardState[pos2] = BoardState[pos1];

				BoardState[pos1]->setPos(getAbsPosition(pos2));
				BoardState[pos1]->Touch();

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

	Pos temp=getCoordFromNumber(index);
	if ((temp.x + temp.y) % 2)
		colSquares[index] = wfield;
	else
		colSquares[index] = bfield;
	marked[index] = 0;
}

void Board::Draw() {

	for (size_t i = 0; i < brd_dim; i++)
	{
		for (size_t j = 0; j < brd_dim; j++)
		{
			int index = j + i * brd_dim;

			
			gameObject::gfx->DrawRect(colSquares[index], squares[index]);
		
		}
	}
	
	int i_max = brd_dim * brd_dim;
	for (int i = 0; i < i_max; i++)
	{
		if(BoardState[i]!=NULL && BoardState[i]!=holdPiece) BoardState[i]->Draw();
	}
	if (holdPiece != NULL)holdPiece->Draw();

}

void Board::drawLegal()
{

	for (size_t i = 0; i < temp_moves.size(); i++)
	{
		int index = temp_moves[i];
		SDL_Color temp;
		temp.r = (colSquares[index].r + 120) / 2;
		temp.g = (colSquares[index].g + 228) / 2;
		temp.b = (colSquares[index].g + 148) / 2; temp.a = 255;
		colSquares[index] = temp;

	}
	legalDrawn = true;

}
void Board::unmarkLegal() {

	for (size_t i = 0; i < temp_moves.size(); i++)
	{
		unmark(temp_moves[i]);
	}
	legalDrawn = false;
}


