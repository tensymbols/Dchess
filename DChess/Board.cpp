#include "Board.h"
#include "texmng.h"

#include <iostream>
#include <string>

using namespace std;
constexpr int FIND_CHECKS = 0;
constexpr int FIND_LEGAL  = 1;
constexpr int REAL_BOARD  = 1;
constexpr int TEMP_BOARD  = 0;
// 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn 

constexpr int WHITE_ROOK	= 0;
constexpr int WHITE_KING	= 1;
constexpr int WHITE_QUEEN	= 2;
constexpr int WHITE_KNIGHT  = 3;
constexpr int WHITE_BISHOP  = 4;
constexpr int WHITE_PAWN	= 5;
constexpr int BLACK_ROOK	= 6;
constexpr int BLACK_KING	= 7;
constexpr int BLACK_QUEEN	= 8;
constexpr int BLACK_KNIGHT  = 9;
constexpr int BLACK_BISHOP  = 10;
constexpr int BLACK_PAWN	= 11;


Board::Board(const char* texfile, Pos pos_, SDL_Color wf, SDL_Color bf, int brd_dim, int sqr_dim) :
	gameObject(texfile, pos_, sqr_dim* brd_dim, sqr_dim* brd_dim), bfield(bf), wfield(wf), sqr_dim(sqr_dim), brd_dim(brd_dim)
{
	U = new util(pos_, sqr_dim, brd_dim);
	b_size = brd_dim * brd_dim;
	holdPiece = NULL;

	BoardState = (Piece**)malloc( sizeof( Piece) * b_size);


	colSquares = new SDL_Color[b_size];
	squares = new SDL_Rect[b_size];

	marked = new bool[b_size];

	for (size_t i = 0; i < b_size; i++) { // 
		BoardState[i] = NULL;
		marked[i] = 0;
	}
	for (size_t i = 0; i < brd_dim; i++) // squares color init
	{
		for (size_t j = 0; j < brd_dim; j++)
		{
			int index = j + i * brd_dim;
			if ((i + j) % 2)
				colSquares[index] = wf;
			else
				colSquares[index] = bf;
		}
	}

	///////////////

	TTF_Font* numberFont = TTF_OpenFont("fonts\\arial.ttf", (int)sqr_dim * 0.6);
	Pos shift = { (int)sqr_dim * 0.2,(int)sqr_dim * 0.2 }; // shift for text indexes
	for (int i = 0; i < brd_dim; i++)
	{
		for (int j = 0; j < brd_dim; j++)
		{
			Pos abs = { this->getPos().x + j * sqr_dim,	this->getPos().y + i * sqr_dim };

			int index = U->getNumberFromCoord({ j,i });
			squares[index].w = sqr_dim,
				squares[index].h = sqr_dim;
			squares[index].x = abs.x;
			squares[index].y = abs.y;

			numberText.push_back(new text(abs + shift, { 255,200,0,255 }, numberFont, std::to_string(index)));
			numberText[index]->setTexAlpha(0);
		}
	}
	///////////////
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
void Board::Init(char* fen)
{
	system("CLS");
	//std::cout << "flushing " << std::flush;
	//WHITE 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn 
	//BLACK 6 - rook, 7 - king, 8 - queen, 9 - knight, 10 - bishop, 11 - pawn 

	if (!initialized) {
		strcpy(_fen, fen);
	}
	else {
		for (size_t i = 0; i < pieces_.size(); i++)
			delete pieces_[i];
		/*for (size_t i = 0; i < tempPieces_.size(); i++)
			delete tempPieces_[i];*/
		unmarkLegal();
		pieces_.clear();


		if(pMenu) delete pMenu;
		delete[] BoardState;
		holdPiece, BoardState, pMenu = NULL;

		BoardState = (Piece**)malloc(sizeof(Piece) * b_size);

		for (size_t i = 0; i < b_size; i++)
			BoardState[i] = NULL;

	}

	// fen reading;
	check = -1;
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

			ttype = U->getTypeFromLetter(fen[k]);
			tcolor = (ttype < 6);

			std::string sNum = to_string(ttype);
			std::string tempTexName = "textures\\pieces_";
			tempTexName += sNum;
			tempTexName += ".png";

			Pos absPos = U->getAbsPosition(pos);
			std::vector<Pos> deltas = U->deltasFromType(ttype);
			int depth = U->depthFromType(ttype);
			if (depth == -1) depth = brd_dim;
			//	std::cout << AbsPosition.x << " " << AbsPosition.y << "\n";
			BoardState[pos] = new Piece(ttype, tcolor, pos, tempTexName.c_str(),
				absPos, sqr_dim, sqr_dim, deltas, depth);

			pieces_.push_back(BoardState[pos]);
		

			if (ttype == 1) wKing = pieces_[pieces_.size() - 1];
			else if (ttype == 7) bKing = pieces_[pieces_.size() - 1];

		

			pos++;
		}
		k++;
	}

	std::cout << "INIT\n";
	initialized = true;
	nextTurn();
}


void Board::changeColor(SDL_Color w, SDL_Color b)
{
	wfield = w;
	bfield = b;
}



void Board::keepInsde(Pos& pos)
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

void Board::handleEvent(SDL_Event& e)
{
	if (pMenu) {
		int response = pMenu->handleEvent(e);
		if (response) {
			endPromotion();
		}
	}
	switch (e.type) {
	case SDL_MOUSEMOTION:

		Pos mpos;
		mpos.x = e.motion.x;
		mpos.y = e.motion.y;

		if (isInside(mpos)) {
			if (holdPiece != NULL) {

				holdPiece->setPos({ mpos.x - sqr_dim / 2,mpos.y - sqr_dim / 2 }); // if there is a held piece it will drag it with mouse cursor
			}
			int pos_ = U->getPosFromMouse(mpos);

			prevMarked = pos_;
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
					int pos_ = U->getPosFromMouse(mpos);

					if (BoardState[pos_] != NULL) {
						// if mouse position is inside board and square where mouse is at is not empty holdpiece is initialized
						if (BoardState[pos_]->getColor() != sideToMove) {
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
			if (RMB_STATE == 0 && LMB_STATE == 0) {

				RMB_STATE = true;
				int x, y;
				unmarkLegal();
				SDL_GetMouseState(&x, &y);
				Pos mpos; mpos.x = x; mpos.y = y;
				if (isInside(mpos))
				{  // if mouse is inside board
					int pos_ = U->getPosFromMouse(mpos);
					if (BoardState[pos_] != NULL) {
						BoardState[pos_] = NULL;
						turn();
					}
				}

			}
		}
		break;
	case SDL_MOUSEBUTTONUP: // when mouse button is released
		if (e.button.button == SDL_BUTTON_LEFT) {
			LMB_STATE = 0;
			int x, y;

			//	std::cout << LMB_STATE << "\n";
			SDL_GetMouseState(&x, &y);
			Pos mpos; mpos.x = x; mpos.y = y;


			if (holdPiece != NULL) {
				if (isInside(mpos)) {  // if mouse is inside board
					int pos_ = U->getPosFromMouse(mpos);


					if (holdPiece->isMoveA(pos_)) { // if move is legal
						if (U->sameSide(holdPiece, BoardState[pos_])) {
							castling(holdPiece, BoardState[pos_]);
						}
						else
						{
							move(holdPiece->getBrdPos(), pos_, REAL_BOARD); // move piece to specified position

						}
						if (shouldBePromoted(holdPiece)) {
							std::cout << "SHOULD BE PROMOTED\n";
							Pos pPos = holdPiece->getPos();
							pPos -= {sqr_dim / 2, sqr_dim / 2};
							pMenu = new promotionMenu(pPos , sqr_dim * 1.2, holdPiece->getColor(), promotionTypes, U, holdPiece);
							clearMoves();
						}
						else {
							unmarkLegal();
							nextTurn();
						}

					}
					else {
						move(holdPiece->getBrdPos(), holdPiece->getBrdPos(), REAL_BOARD); // if not legal then move piece back

					}

				}
				else {
					move(holdPiece->getBrdPos(), holdPiece->getBrdPos(), REAL_BOARD); // if mouse is outside the board bring held piece back

				}

			}

			holdPiece = NULL;
		}

		else if (e.button.button == SDL_BUTTON_RIGHT) {
			if (RMB_STATE == 1) {
				RMB_STATE = 0;
			}
		}
		break;
	}
}
void Board::clearMoves() {
	for (size_t i = 0; i < b_size; i++)
	{
		if (BoardState[i] != NULL) BoardState[i]->clearMoves();
	}
}
void Board::clearMoves(std::vector<Piece*> exceptions) {
	for (size_t i = 0; i < b_size; i++)
	{
		if (BoardState[i] != NULL) {
			std::vector<Piece*>::iterator it = std::find(exceptions.begin(), exceptions.end(), BoardState[i]);
			if(it==exceptions.end()) BoardState[i]->clearMoves();
		}
	}
}
void Board::nextTurn()
{
	sideToMove = !sideToMove;
	turn();
	
}
void Board::turn() {

	clearMoves();


	for (size_t i = 0; i < b_size; i++)
	{

		if (BoardState[i] != NULL && sideToMove == BoardState[i]->getColor())
		{
			allPseudoLegal(BoardState[i]);

		}
	}
	if (sideToMove == true)
		getAllLegal(wKing);
	else
		getAllLegal(bKing);

	if (check == -1) {
		if (sideToMove == true)
			addCastlingMoves(wKing);
		else
			addCastlingMoves(bKing);
	}

}

void Board::allPseudoLegal(Piece* p) { // part of available moves (for all pieces except pawn)

	
	//WHITE 0 - rook, 1 - king, 2 - queen, 3 - knight, 4 - bishop, 5 - pawn 
	//BLACK 6 - rook, 7 - king, 8 - queen, 9 - knight, 10 - bishop, 11 - pawn 
	std::vector<Pos> deltas = p->getDeltas();
	int depth = p->getDepth();
	int currPos = p->getBrdPos();

	Piece** board = BoardState;

	//if (!israelboard) tempPieces_ = pieces_;
	Pos coord = U->getCoordFromNumber(currPos); // from n to { x,y }

	if (p->getType() % 6 == 5) {
		int sign = (p->getColor()) ? -1 : 1;
		// manually adding legal moves to pawns bc its moves cant be described with deltas
		int numPos = currPos + (brd_dim)*sign;
		if (U->isPosLegal(numPos) && board[numPos] == NULL) {
			BoardState[currPos]->addMove(numPos);
			if (board[currPos]->isUntouched()) {
				numPos = currPos + (2 * brd_dim * sign);
				if (U->isPosLegal(numPos) && board[numPos] == NULL) board[currPos]->addMove(numPos);
			}
		}

	}

	Pos delta;
	if (depth == -1) depth = brd_dim;
	for (size_t i = 0; i < deltas.size(); i++)
	{
	
		delta = deltas[i];
		coord += delta;

		for (size_t currDepth = 0; currDepth < depth &&
			coord.x >= 0 && coord.x < brd_dim &&
			coord.y >= 0 && coord.y < brd_dim;
			currDepth++)

		{

			int t_pos = U->getNumberFromCoord(coord); // from { x, y } to n
			if (board[t_pos] == NULL) {
				if (p->getType() % 6 != 5) board[currPos]->addMove(t_pos); // if square is empty we can go there
				
			}
			else {
				if (board[t_pos]->getColor() != board[currPos]->getColor()) {
					p->addMove(t_pos); // if we bump into piece of opposite color this is our last square in this direction that we can go to
				}
				
				break;
			}

			coord += delta;
		}
		coord = U->getCoordFromNumber(currPos);
	}


}

/////////////////////////////////////////////////////////////// check block 

bool Board::shouldBePromoted(Piece *p)
{
	if (!p->isUntouched()
		&& p->getType() == BLACK_PAWN
		&& U->getCoordFromNumber( p->getBrdPos() ).y == brd_dim-1 )
	{
		return true;
	}
	if (!p->isUntouched()
		&& p->getType() == WHITE_PAWN 
		&& U->getCoordFromNumber( p->getBrdPos() ).y == 0)
	{
		return true;
	}
	return false;
}

void Board::getAllLegal(Piece* p) {


	std::cout << "\nW KINGPOS " << wKing->getBrdPos() << "\n";
	std::cout << "B KINGPOS " << bKing->getBrdPos() << "\n";



	// casting "rays" in queen and knight directions combined because those are directions that pieces can check king through

	/// Correcting King(or potentially other piece) moves so that it wont be able to march into check

	std::vector<int> legit_moves = safeFieldsAround(p);

	p->addMoves(legit_moves);


	processCheck(p);

	processTiedPieces(p);


}



void Board::addCastlingMoves(Piece* p)
{
	if (!p->isUntouched()) return;
	
	int k_pos = p->getBrdPos();
	
	bool side = p->getColor();
	int k = (side) ? 0 : 6;   // type 1 or 7 (white or black rook)

	vector<int> path;
	vector<pair<int, Pos>> rook;

	getPiecesInReach({ {-1,0} }, p, brd_dim / 2, side, rook, &path);

	
	if (!rook.empty()
		&& BoardState[rook[0].first]->getType() == WHITE_ROOK + k
		&& BoardState[rook[0].first]->isUntouched()
		&& U->isPosLegal(k_pos - 2) ){

		bool after_attacked = false;
		bool under_attack = false;

		after_attacked |= findAttackers(U->deltasFromType(WHITE_QUEEN), k_pos - 2, brd_dim, !sideToMove); // check if castling wont lead to check
		after_attacked |= findAttackers(U->deltasFromType(WHITE_KNIGHT), k_pos - 2, 1, !sideToMove);
		
		// logic above is actually useless in regular chess, bc king cant appear on rook's position, that is under attack
		// but i tried to do this as flexible as possible

	
		for (size_t i = 0; i < path.size(); i++)
		{
			under_attack |= findAttackers(U->deltasFromType(WHITE_QUEEN), path[i], brd_dim, !sideToMove);
			under_attack |= findAttackers(U->deltasFromType(WHITE_KNIGHT), path[i], 1, !sideToMove);
		}
		if (!under_attack && !after_attacked) {
			p->addMove(rook[0].first);
		}
	}

	path.clear();
	rook.clear();

	getPiecesInReach({ {1,0} }, p, brd_dim / 2, side, rook, &path);

	if (!rook.empty()
		&& BoardState[rook[0].first]->getType() == WHITE_ROOK + k
		&& BoardState[rook[0].first]->isUntouched()
		&& U->isPosLegal(k_pos + 2)) {

		bool after_attacked = false;
		bool under_attack = false;

		after_attacked |= findAttackers(U->deltasFromType(WHITE_QUEEN), k_pos + 2, brd_dim, !sideToMove); // check if castling wont lead to check
		after_attacked |= findAttackers(U->deltasFromType(WHITE_KNIGHT), k_pos + 2, 1, !sideToMove);


		for (size_t i = 0; i < path.size(); i++)
		{
			under_attack |= findAttackers(U->deltasFromType(WHITE_QUEEN), path[i], brd_dim, !sideToMove);
			under_attack |= findAttackers(U->deltasFromType(WHITE_KNIGHT), path[i], 1, !sideToMove);
		}
		if (!under_attack && !after_attacked) {
			p->addMove(rook[0].first);
		}
	}

}

void Board::castling(Piece* p1, Piece* p2) {
	bool k_or_q = (p1->getBrdPos() - p2->getBrdPos()) > 0;
	int k_pos = p1->getBrdPos();
	int r_pos = p2->getBrdPos();
	int c_pos = -1;
	int k = (k_or_q) ? -1 : 1;
	 // if its queen side
	c_pos = k_pos + (1 * k);
	if (U->isPosLegal(c_pos)) {
		move(r_pos, c_pos, REAL_BOARD);// moving rook 
	}
	c_pos = k_pos + (2*k);
	if (U->isPosLegal(c_pos)) {
		move(k_pos, c_pos, REAL_BOARD); // moving king 
	}


}

void Board::endPromotion()
{
	delete pMenu;
	pMenu = NULL;
	nextTurn();
}

std::vector<int> Board::safeFieldsAround(Piece* p)
{
	std::vector<int> temp_moves = p->getMoves();
	std::vector<int> legit_moves;
	p->clearMoves();

	std::vector<int> field_attackers;
	std::vector<int> temp_path;
	for (size_t i = 0; i < temp_moves.size(); i++) // adding temp move to available moves if square is not attacked
	{
		int curr = temp_moves[i];

		findAttackers(U->deltasFromType(WHITE_QUEEN), curr, brd_dim, !sideToMove, &field_attackers, &temp_path, p); // finding attackers of current field (ignoring our king piece)
		findAttackers(U->deltasFromType(WHITE_KNIGHT), curr, 1, !sideToMove, &field_attackers, &temp_path, p);

		if (field_attackers.size() == 0) {
			legit_moves.push_back(temp_moves[i]);
		}
		else {
			std::cout << "pos:" << curr << " attackers number: " << field_attackers.size() << "\n";
			std::cout << "attackers list: ";
			U->displayIntVector(field_attackers);
			std::cout << "\n";
		}
		field_attackers.clear();

	}
	return legit_moves;
}


void Board::processCheck(Piece* p)
{
	bool this_side = p->getColor();
	bool opposite_side = !this_side;
	Piece** board = BoardState;
	int kingFound = 0;
	int piecePos = p->getBrdPos();

	std::vector<int> piece_attackers;

	std::vector<int> path;

	findAttackers(U->deltasFromType(WHITE_QUEEN), piecePos, brd_dim, opposite_side, &piece_attackers, &path); // depth -1 = infinity, queen deltas

	findAttackers(U->deltasFromType(WHITE_KNIGHT), piecePos, 1, opposite_side,&piece_attackers, &path); // knight deltas
	if (piece_attackers.size() > 0) {
		check = this_side;
		if (piece_attackers.size() > 1) {
			clearMoves({ p }); // clear all pieces moves except our piece

			/*std::cout << "MULTIPLE CHECK FROM: ";
			U->displayIntVector(piece_attackers);
			std::cout << "\n";
			std::cout << "PATH: ";
			U->displayIntVector(path);*/

		}
		if (piece_attackers.size() == 1) {

			/*std::cout << "SINGLE CHECK FROM: " << piece_attackers[0] << "\n";
			std::cout << "PATH: ";
			U->displayIntVector(path);*/

			std::vector<int> p_intersection;

			for (size_t i = 0; i < b_size; i++)
			{
				if (U->sameSide(board[i], p) && board[i] != p) {
					Piece* ally = board[i];

					temp_moves = ally->getMoves();
					p_intersection = U->getIntersection(temp_moves, path);
					ally->clearMoves();
					ally->addMoves(p_intersection);
				}
			}

		}

	}
}


bool Board::getPiecesInReach(std::vector<Pos> deltas, Piece* p, int depth, bool colorToFind,
	std::vector<std::pair<int, Pos >>& pieces, std::vector<int>* path) { // part of available moves (for all pieces except pawn)

	int currPos = p->getBrdPos();

	Piece** board = BoardState;


	Pos coord = U->getCoordFromNumber(currPos); // from n to { x,y }

	if (p->getType() % 6 == 5) {

		int sign = (p->getColor()) ? -1 : 1;
		// manually adding legal moves to pawns bc its moves cant be described with deltas
		int numPos = currPos + (brd_dim - 1) * sign;
		Pos currDelta = { 0, 1 * sign };
		if (U->isPosLegal(numPos) && board[numPos] != NULL && board[numPos]->getColor() == colorToFind) {

			pieces.push_back(std::make_pair(numPos, currDelta));
		}
		else if (board[currPos]->isUntouched() && board[numPos] == NULL) {
			numPos = currPos + (2 * brd_dim * sign);
			if (U->isPosLegal(numPos) && board[numPos] != NULL && board[numPos]->getColor() == colorToFind) {
				pieces.push_back(std::make_pair(numPos, currDelta));
			}
		}

	}

	Pos delta;

	for (size_t i = 0; i < deltas.size(); i++)
	{
		//path.clear();
		delta = deltas[i];
		coord += delta;

		for (size_t currDepth = 0; currDepth < depth && coord.x >= 0 && coord.x < brd_dim
			&& coord.y >= 0 && coord.y < brd_dim; currDepth++)

		{
			int t_pos = U->getNumberFromCoord(coord); // from { x, y } to n

			if (board[t_pos] != NULL) {
				if (board[t_pos]->getColor() == colorToFind) {
					pieces.push_back(make_pair(t_pos, delta));
				}
				break;
			}
			if (path) path->push_back(t_pos);
			coord += delta;
		}

		coord = U->getCoordFromNumber(currPos);
	}


	return pieces.size() > 0;

}


bool Board::findAttackers(std::vector<Pos> deltas, int attackedPos, int depth, bool colorToFind,
	std::vector<int>* attackers, std::vector<int>* path, Piece* ignore) { // part of available moves (for all pieces except pawn)

	int currPos = attackedPos;

	std::vector<int> tempPath;

	Piece** board = BoardState;


	Pos coord = U->getCoordFromNumber(currPos); // from n to { x,y }

	Pos delta;

	for (size_t i = 0; i < deltas.size(); i++)
	{

		delta = deltas[i];
		coord += delta;
		tempPath.clear();
		for (size_t currDepth = 0; currDepth < depth && coord.x >= 0 && coord.x < brd_dim
			&& coord.y >= 0 && coord.y < brd_dim; currDepth++)

		{

			int t_pos = U->getNumberFromCoord(coord); // from { x, y } to n

			if (board[t_pos] != NULL) {
				if (board[t_pos]->getColor() == colorToFind
					&& board[t_pos]->hasDelta(delta.opposite())
					&& board[t_pos]->getDepth() >= (currDepth + 1))
				{
					if (attackers) {
						attackers->push_back(t_pos);
					}
					else { 
						return true; 
					}
					tempPath.push_back(t_pos);
					if(path) path->insert(path->end(), tempPath.begin(), tempPath.end());
				}

				if (board[t_pos] != ignore) 	break;

			}
			else {
				tempPath.push_back(t_pos);
			}

			coord += delta;
		}

		coord = U->getCoordFromNumber(currPos);
	}


	return false;

}


void Board::processTiedPieces(Piece* p)
{
	Piece** board = BoardState;
	bool this_side = p->getColor();
	bool opposite_side = !this_side;
	int piecePos = p->getBrdPos();

	std::vector<int> ghost_attackers;
	std::vector<int> ghost_path;

	std::vector<std::pair<int, Pos> > nearby_allies;

	getPiecesInReach(U->deltasFromType(2), p, brd_dim, this_side, nearby_allies);

	std::vector<int> p_intersection;

	for (size_t i = 0; i < nearby_allies.size(); i++)
	{
		Piece* ally = board[nearby_allies[i].first];
		std::vector<Pos> deltas = { nearby_allies[i].second };

		findAttackers(deltas, piecePos, brd_dim, opposite_side, &ghost_attackers, &ghost_path, ally);


		if (!ghost_attackers.empty()) {
			int last_ix = ghost_attackers.size() - 1;
			int attacker_pos = ghost_attackers[last_ix];

			temp_moves = ally->getMoves();

			p_intersection = U->getIntersection(temp_moves, ghost_path);

			ally->clearMoves();
			ally->addMoves(p_intersection);
		}
		ghost_attackers.clear();
		ghost_path.clear();
	}
}

/////////////////////////////////////////////////////////////// check block end

void Board::move(int pos1, int pos2, bool realBoard)
{
	Piece** board = BoardState;
	try {
		if (pos1 == pos2) {
			board[pos1]->setPos(U->getAbsPosition(pos2));
		}
		else {
			//	std::cout << BoardState[pos1_] << " " << BoardState[pos2_];
			if (board[pos1] == NULL) {
				std::cout << ("Illegal move\n");
			}
			else {
				board[pos1]->Move(pos2);

				board[pos1]->clearMoves();
				//delete BoardState[pos2];

				board[pos2] = board[pos1];

				board[pos1]->setPos(U->getAbsPosition(pos2));
				board[pos1]->Touch();

				board[pos1] = NULL;

				check = -1;

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
	temp.r = (colSquares[index].r + 255) / 2;
	temp.g = colSquares[index].g / 2;
	temp.b = colSquares[index].b / 2; temp.a = 255;
	colSquares[index] = temp;
	marked[index] = 1;
}
void Board::unmark(const int index)
{

	Pos temp = U->getCoordFromNumber(index);
	if ((temp.x + temp.y) % 2)
		colSquares[index] = wfield;
	else
		colSquares[index] = bfield;
	marked[index] = 0;
}

void Board::toggleNumbers()
{
	if (showNumbers == true) {
		for (size_t i = 0; i < numberText.size(); i++)
		{
			numberText[i]->setTexAlpha(0);
		}
		showNumbers = false;
	}
	else {
		for (size_t i = 0; i < numberText.size(); i++)
		{
			numberText[i]->setTexAlpha(255);
		}
		showNumbers = true;
	}
}

void Board::togglePiecesAlpha()
{
	if (alphaPieces == true) {
		for (size_t i = 0; i < pieces_.size(); i++)
		{
			pieces_[i]->setTexAlpha(70);
		}
		alphaPieces = false;
	}
	else {
		for (size_t i = 0; i < pieces_.size(); i++)
		{
			pieces_[i]->setTexAlpha(255);
		}
		alphaPieces = true;
	}
}

void Board::Draw() {

	for (size_t i = 0; i < brd_dim; i++)
	{
		for (size_t j = 0; j < brd_dim; j++)
		{
			int index = j + i * brd_dim;


			gameObject::gfx->DrawRect(colSquares[index], squares[index]);
			numberText[index]->Draw();
		}
	}

	int i_max = brd_dim * brd_dim;
	for (int i = 0; i < i_max; i++)
	{
		if (BoardState[i] != NULL && BoardState[i] != holdPiece) BoardState[i]->Draw();
	}
	if (holdPiece != NULL)holdPiece->Draw();

	if (pMenu) pMenu->Draw();
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

