#include "promotionMenu.h"
#include <string>
using namespace std; 

promotionMenu::promotionMenu(Pos pos, int dim, bool color, vector<int> types, util* U, Piece* toPromote) :
	types_(types), color_(color), dim_(dim), U(U), toPromote(toPromote), gameObject(NULL, pos, dim* types.size(), dim)
{

	int k = (color) ? 0 : 6;
	for (size_t i = 0; i < types.size(); i++)
	{
		string tempTexName;
		tempTexName = "textures\\pieces_";
		string typeNum = to_string(types[i] + k);
		tempTexName = tempTexName + typeNum + ".png";
		piecesTex.push_back(texLoader::loadTexture(tempTexName.c_str(), rnd));
		SDL_Rect r = { this->pos_.x + dim * i,this->pos_.y, dim, dim };
		squares.push_back(r);
		squares_cl.push_back({ 255,255,255,100 });
	}

}

/*promotionMenu::promotionMenu(int type, util* U, Piece* toPromote) : gameObject(NULL, {})
{
	toPromote->setType(type);
	toPromote->setDeltas(U->deltasFromType(type));
	toPromote->setDepth(U->depthFromType(type));
}*/
void promotionMenu::promote(int typeIndex)
{
	toPromote->setType(types_[typeIndex]);
	toPromote->setDeltas(U->deltasFromType(types_[typeIndex]));
	toPromote->setDepth(U->depthFromType(types_[typeIndex]));

	toPromote->setTexture(piecesTex[typeIndex]);
}

int promotionMenu::handleEvent(SDL_Event& e)
{
	Pos mpos;
	int ix;
	switch (e.type) {

	case SDL_MOUSEMOTION:
		mpos.x = e.motion.x;
		mpos.y = e.motion.y;

		ix = ixInside(mpos);
		if (ix != -1) {
			squares_cl[ix] = { 200,200,200,100 };
		}
		if (prevIx != -1 && prevIx != ix) {
			squares_cl[prevIx] = { 230,240,230,100 };
		}
		prevIx = ix;

		break;
	case SDL_MOUSEBUTTONDOWN:

		break;
	case SDL_MOUSEBUTTONUP:
		int x, y;
		SDL_GetMouseState(&x, &y);
		mpos.x = x; mpos.y = y;

		ix = ixInside(mpos);
		if (ix != -1) {
			promote(ix);
			return 1;
		}
		break;
	}
	return 0;
}

void promotionMenu::Draw()
{
	for (size_t i = 0; i < piecesTex.size(); i++)
	{

		gameObject::gfx->DrawRect(squares_cl[i], squares[i]);
		SDL_RenderCopy(rnd, piecesTex[i], NULL, &squares[i]);

	}
}

int promotionMenu::ixInside(Pos pos)
{
	if (!isInside(pos)) return -1;
	Pos relPos = pos - this->pos_;

	return relPos.x / dim_; // buttons are arranged in line so no need in y coordinate processing
}
