#pragma once
#include "gameObject.h"
#include <vector>
#include "piece.h"
#include "text.h"
#include "util.h"
#include <utility>   
class Board : public gameObject {
public:

	using gameObject::Move;
	Board(const char*, Pos, SDL_Color wf, SDL_Color bf, int brd_dim, int sqr_dim);
	~Board();
	void Init(char* fen);
	void Init();
	void Draw() override; // draws board and pieces
	void drawLegal();
	void unmarkLegal();


	void move(int pos1, int pos2, bool realBoard); // move function from one position to another (numbers)

	/////////////////////

	void mark(const int); // mark square with color
	void unmark(const int); // unmark square
	void toggleNumbers();
	void togglePiecesAlpha();

	/////////////////////

	void keepInsde(Pos&); // keep piece inside while dragging when mouse position is out of board borders on screen

	void handleEvent(SDL_Event&); // handles events like mouse etc 

	void nextTurn();
	void turn();

	void clearMoves();
	void clearMoves(std::vector<Piece*> exceptions);
	bool getPiecesInReach(std::vector<Pos> deltas, Piece* p, int depth, bool colorToFind, std::vector<std::pair<int, Pos >>& pieces, std::vector<int>* path = NULL);
	bool findAttackers(std::vector<Pos> deltas, int attackedPos, int depth, bool colorToFind, std::vector<int>& attackers, std::vector<int>& path, Piece* ignore = NULL);
	
	std::vector<int> safeFieldsAround(Piece* p);
	void processTiedPieces(Piece* p);
	void processCheck(Piece* p);
	void allPseudoLegal(Piece* p);
	
	void getAllLegal(Piece* p);

	//bool isOnTheSameLine()

	void changeColor(SDL_Color, SDL_Color);
private:
	util* U;
	int check = -1;
	bool sideToMove = 0;// 0 - black, 1 - white
	int semiClock = 0;
	int fullClock = 0;
	int sqr_dim = 0;
	int brd_dim = 0;
	int b_size = 0;

	SDL_Color bfield;
	SDL_Color wfield;
	//////////////

	std::vector<int> temp_moves;

	//////////////

	int prevMarked = 0;
	bool legalDrawn = false;
	bool initialized = false;
	bool showNumbers = false;
	bool alphaPieces = true;
	bool LMB_STATE = false;
	bool RMB_STATE = false;
	//////////////

	char _fen[256]= " ";



	bool* marked;
	Piece* tempPiece = NULL;
	Piece* holdPiece = NULL;
	Piece* bKing = NULL;
	Piece* wKing = NULL;

	SDL_Color* colSquares = NULL;
	SDL_Rect* squares = NULL;

	std::vector<Piece*> pieces_;


	std::vector<text*> numberText;

	Piece** BoardState = NULL;// contains "references" to pieces, refers to NULL when cell is not occupied*/

};


