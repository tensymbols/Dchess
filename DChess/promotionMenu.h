#pragma once

#include "gameObject.h"
#include <vector>
#include "piece.h"
#include "util.h"
#include "texmng.h"

using namespace std;

class promotionMenu : public gameObject {
public:

	promotionMenu(Pos pos, int dim, bool color, std::vector<int> types, util* U, Piece* toPromote);

	promotionMenu(int type, util* U, Piece* toPromote);
	void promote(int typeIx);
	int handleEvent(SDL_Event& e);
	void Draw() override;
	int ixInside(Pos pos);
private:
	vector<SDL_Texture*> piecesTex;
	Piece* toPromote;

	bool RMB_STATE = false;
	bool LMB_STATE = false;
	vector<int> types_;
	int dim_ = 0;
	bool color_ = false;
	vector<SDL_Rect> squares;
	vector<SDL_Color> squares_cl;

	util* U;

	int prevIx = -1;
};