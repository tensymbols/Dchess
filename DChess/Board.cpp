#include "Board.h"
#include <iostream>
#include <string>
	
#define FIND_CHECKS 0
#define FIND_LEGAL 1
#define REAL_BOARD 1
#define TEMP_BOARD 0

Board::Board(const char* texfile, Pos pos_, SDL_Color wf, SDL_Color bf, int brd_dim ,int sqr_dim) :
	gameObject(texfile,  pos_,sqr_dim*brd_dim,sqr_dim*brd_dim), bfield(bf), wfield(wf), sqr_dim(sqr_dim), brd_dim(brd_dim)
{
	int b_size = brd_dim * brd_dim;
	holdPiece = NULL;
	BoardState = new Piece*[b_size];
	tempBoard = new Piece * [b_size];
	marked = new bool[b_size];
	colSquares = new SDL_Color[b_size];
	squares = new SDL_Rect[b_size];

	for (size_t i = 0; i < b_size; i++) { // 
		BoardState[i] = NULL;
		marked[i] = 0;
	}
	for (int i = 0; i < brd_dim; i++) // squares color init
	{
		for (int j = 0; j < brd_dim; j++)
		{
			int index = j + i * brd_dim;
			if ((i + j) % 2)
				colSquares[index] = wf;
			else
				colSquares[index] = bf;
		}
	}
	fullClock = 0;
	semiClock = 0;
	sideToMove = 0;
	for (int i = 0; i < brd_dim; i++)
	{
		for (int j = 0; j < brd_dim; j++)
		{
			int index = getNumberFromCoord({j,i});
			squares[index].w = sqr_dim,
			squares[index].h = sqr_dim;
			squares[index].x = this->getPos().x + j * sqr_dim;
			squares[index].y = this->getPos().y + i * sqr_dim;
		}
	}

}

Board::~Board()
{
	delete[] marked;
	delete[] colSquares;
	delete[] squares;
	delete[] BoardState;
}
void Board::Init() {
	Init(_fen);
}
void Board::Init( char* fen)
{
	//WHITE 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn 
	//BLACK 6 - rook, 7 - king, 8 - queen, 9 - knight, 10 - bishop, 11 - pawn 
	
	if(!initialized)strcpy(_fen, fen);
	if (initialized) {
		
		unmarkLegal();
		pieces_.clear();
		temp_moves.clear();
		holdPiece = NULL;

		for (size_t i = 0; i < pieces_.size(); i++)
			delete pieces_[i];

		delete[] BoardState; 
		int b_size = brd_dim * brd_dim;

		BoardState = new Piece * [b_size];
		for (size_t i = 0; i < b_size; i++)
			BoardState[i] = NULL;
		
	}
	
	// fen reading;
	sideToMove = 0;
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

			if (ttype == 1) wKing = pieces_[pieces_.size() - 1];
			if (ttype == 7) bKing = pieces_[pieces_.size() - 1];

			BoardState[pos] = pieces_[pieces_.size() - 1];
			

			pos++;
		}
		k++;
	}
	std::cout << "INIT";
	initialized = true;
	nextTurn();
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
	int pos_ = j * brd_dim + i;
	return pos_;
}


Pos Board::getCoordFromNumber(const int pos)
{

	int y = pos / brd_dim;
	int x = pos-y*brd_dim;

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
	int x_right = brdpos.x + sqr_dim * brd_dim;
	int y_down = brdpos.y + sqr_dim * brd_dim;
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
		//	unmark(prevMarked);
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
				unmarkLegal();
				if (isInside(mpos)) {
					int pos_ = getPosFromMouse(mpos);
					
					if (BoardState[pos_] != NULL) {
						// if mouse position is inside board and square where mouse is at is not empty holdpiece is initialized
						if (BoardState[pos_]->GetColor() != sideToMove) {
							if (sideToMove)
								std::cout << "Its  " << " white's " << " turn now\n";
							else std::cout << "Its  " << " black's " << " turn now\n";
							temp_moves = std::vector<int>(0);
						}
						else {
							holdPiece = BoardState[pos_];
	
							temp_moves = holdPiece->getMoves();
							drawLegal();
						}
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


						if (holdPiece->isMoveA(pos_)) { // if move is legal
							move(holdPiece->GetPos(), pos_, REAL_BOARD); // move piece to specified position
							unmarkLegal();
							nextTurn();

							
						}
						else {
							move(holdPiece->GetPos(), holdPiece->GetPos(), REAL_BOARD); // if not legal then move piece back

						}

					}
					else {
						move(holdPiece->GetPos(), holdPiece->GetPos(), REAL_BOARD); // if mouse is outside the board bring held piece back

					}
					
				}
				
				holdPiece = NULL;
			}

		}
		else if (e.button.button == SDL_BUTTON_RIGHT) {

		}		break;
	}
}
void Board::nextTurn()
{
	sideToMove = !sideToMove;

	for (size_t i = 0; i < pieces_.size(); i++)
	{
		pieces_[i]->clearMoves();
		allPseudoLegal(pieces_[i], REAL_BOARD);

	}
	processCheck(sideToMove);
}


void Board::legal(std::vector<Pos>& deltas, Piece* p, int depth, int typeOfcheck, bool israelboard) { // part of available moves (for all pieces except pawn)

	int pos = p->GetPos();
	
	Piece** board = (israelboard) ? BoardState : tempBoard;

	//if (!israelboard) tempPieces_ = pieces_;
	Pos coord = Board::getCoordFromNumber(pos);

	
	Pos delta;
	for(size_t i=0; i<deltas.size();i++)
	{
		delta=deltas[i];
		coord += delta;

		for (size_t i = 0; i < depth && coord.x >= 0 && coord.x < brd_dim &&
			coord.y >= 0 && coord.y < brd_dim; i++)

		{
			int t_pos = getNumberFromCoord(coord);
			if (board[t_pos] == NULL) {
				if(typeOfcheck == FIND_LEGAL) board[pos]->addMove(t_pos); // if square is empty we can go there
				
			}
			else {
				if (board[t_pos]->GetColor() != board[pos]->GetColor()) {
					p->addMove(t_pos); // if we bump into piece of opposite color this is our last square we can go to in this direction
					if(typeOfcheck==FIND_CHECKS) std::cout <<"Potential check " << t_pos << "\n";
				}
		
				break;
			}

			coord += delta;
		}
		coord = Board::getCoordFromNumber(pos);
	}
}
void Board::potentialChecks(Piece* p) { 

	int kingPos = p->GetPos();
	std::cout << "KINGPOS " << kingPos<<"\n";
	std::vector<int> pChecks;

	std::vector<Pos> deltas0 = { {  1,  0 }, { -1,  0 }, {  0, 1 }, { 0, -1 } , // "queen" moves
								 { -1, -1 }, {  1, -1 }, { -1, 1 }, { 1,  1 } };

	std::vector<Pos> deltas1 = { { -2,  1 }, { 2,  1 }, { -1, 2 }, { 1,  2 },// "knight" moves
								 { -2, -1 }, { 2, -1 }, { -1,-2 }, { 1, -2 } };
	// casting "rays" in queen and knight directions combined because those are directions that pieces can check king through

	legal(deltas0, p, brd_dim, FIND_CHECKS, REAL_BOARD);

	legal(deltas1, p, 1, FIND_CHECKS, REAL_BOARD);


} //auxiliary function 

void Board::processCheck(bool side)
{


	Piece* KING = (side) ? wKing :  bKing;
	int kingPos = KING->GetPos();

	Piece P_Temp = *KING;


	memcpy(tempBoard, BoardState, sizeof(BoardState)); // making a copy of current state of board to temporary board


	std::vector<int> inCheck ;
	potentialChecks(&P_Temp);
	std::vector<int> pChecks = P_Temp.getMoves();


	std::vector<int> t_pseudo;

	std::cout << "size " << pChecks.size() << "\n\n\n";
/*	for (size_t i = 0; i < pChecks.size(); i++)
	{

		int ix = pChecks[i];
		std::cout <<"INDEX " << ix << "\n\n\n";
 		t_pseudo = BoardState[ix]->getMoves();
		for (size_t j = 0; j < t_pseudo.size(); j++)
		{
			if (t_pseudo[j] == kingPos) {
				inCheck.push_back(pChecks[i]);
				std::cout << "\n" << pChecks[i] << "\n";
			}

		}
		//BoardState[ix]->clearMoves();

	}*/

	(side) ? w_check = inCheck : b_check = inCheck;

}
void Board::allPseudoLegal( Piece* p, bool realBoard)
{
	Piece** board = (realBoard) ? BoardState : tempBoard;
	std::vector<Piece*>& pieces = (realBoard) ? pieces_ : tempPieces_;

	int ttype = p->GetType();
	ttype %= 6;
	int currPos = p->GetPos();
	//WHITE 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn 
	//BLACK 6 - rook, 7 - king, 8 - queen, 9 - knight, 10 - bishop, 11 - pawn 
	std::vector<int> moves;



	std::vector<int> legal_temp;
	std::vector<Pos> deltas;
	switch (ttype) {
	case 0: {
		deltas = { {1, 0},{-1,0},{ 0,1}, {0,-1} };
		legal(deltas, p, brd_dim, FIND_LEGAL, realBoard);


	}
		  break;
	case 1: {
		deltas = { {1, 0},{-1,0},{ 0,1}, {0,-1} ,{ -1, -1 }, { 1,-1 },{ -1,1 },{ 1,1 } };
		legal(deltas, p, 1, FIND_LEGAL, realBoard);

	}
		  break;
	case 2: {
		deltas = { {1, 0},{-1,0},{ 0,1}, {0,-1} ,{ -1, -1 }, { 1,-1 },{ -1,1 },{ 1,1 } };
		legal(deltas, p, brd_dim, FIND_LEGAL, realBoard);

	}
		  break;
	case 3: {
		deltas = { {-2, 1},{2,1},{ -1,2}, {1,2} ,{ -2, -1 }, { 2,-1 },{ -1,-2 },{1,-2 } };
		legal(deltas, p, 1, FIND_LEGAL, realBoard);
		
		break;
	}
	case 4: {
		deltas = { { -1, -1 }, { 1,-1 },{ -1,1 },{ 1,1 } };
		legal(deltas, p, brd_dim, FIND_LEGAL, realBoard);
		
		break;
	}
	case 5: {
		if (p->GetColor()==1) { //white pawn
			// manually adding legal moves to pawns bc its moves cant be described with legal() function
			int numPos = currPos - brd_dim - 1;
			if (board[numPos] != NULL && board[numPos]->GetColor() !=sideToMove)  board[currPos]->addMove(numPos);

			numPos = currPos - brd_dim + 1;
			if (board[numPos] != NULL && board[numPos]->GetColor() != sideToMove) board[currPos]->addMove(numPos);

			numPos = currPos - brd_dim;
			if (numPos >= 0 && board[numPos] == NULL) {
				BoardState[currPos]->addMove(numPos);
				if (board[currPos]->IsUntouched()) {
					numPos = currPos - 2 * brd_dim;
					if (board[numPos] == NULL) board[currPos]->addMove(numPos);
				}
			}

		} 
		else if (p->GetColor() == 0) { // black pawn
			int numPos = currPos + brd_dim - 1;
			if (board[numPos] != NULL && board[numPos]->GetColor() != sideToMove) board[currPos]->addMove(numPos);

			numPos = currPos + brd_dim + 1;
			if (board[numPos] != NULL && board[numPos]->GetColor() != sideToMove) board[currPos]->addMove(numPos);

			numPos = currPos + brd_dim;
			if (numPos >= 0 && board[numPos] == NULL) {
				BoardState[currPos]->addMove(numPos);
				if (board[currPos]->IsUntouched()) {
					numPos = currPos + 2 * brd_dim;
					if (board[numPos] == NULL) board[currPos]->addMove(numPos);
				}
			}
		}
		break;
		}
	}

}

Pos Board::getAbsPosition(int pos)
{
	Pos position = getCoordFromNumber(pos);
	Pos AbsPosition = { position.x * sqr_dim + this->getPos().x, position.y * sqr_dim + this->getPos().y };
	return AbsPosition;
}


void Board::move(int pos1, int pos2, bool realBoard)
{
	Piece** board = (realBoard) ? BoardState : tempBoard;
	try {
		if (pos1 == pos2) {
			board[pos1]->setPos(getAbsPosition(pos2));
		}
		else {
			//	std::cout << BoardState[pos1_] << " " << BoardState[pos2_];
			if (board[pos1]==NULL) {
				std::cout << ("Illegal move\n");
			}
			else {
				board[pos1]->Move(pos2);

				board[pos1]->clearMoves();
				//delete BoardState[pos2];

				board[pos2] = board[pos1];

				board[pos1]->setPos(getAbsPosition(pos2));
				board[pos1]->Touch();

				board[pos1] = NULL;
				

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


