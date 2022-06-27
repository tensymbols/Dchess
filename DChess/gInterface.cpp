#include "gInterface.h"
#include "Board.h"
gInterface::gInterface(Pos pos_, int iDim, const char* texfile, Board& brd) : gameObject(texfile, pos_, iDim * 6, iDim), brd(brd)
{

	buttons.push_back(new iButton(0, { 0, 0 }, "textures/interface/button0.png", iDim, iDim));
	buttons.push_back(new iButton(1, { iDim * 1, 0 }, "textures/interface/button1.png", iDim, iDim));
	buttons.push_back(new iButton(2, { iDim * 2, 0 }, "textures/interface/button2.png", iDim, iDim));
	buttons.push_back(new iButton(3, { iDim * 3, 0 }, "textures/interface/button3.png", iDim, iDim));
	buttons.push_back(new iButton(4, { iDim * 4, 0 }, "textures/interface/button4.png", iDim, iDim));
	buttons.push_back(new iButton(5, { iDim * 5, 0 }, "textures/interface/button5.png", iDim, iDim));
	// hardcoded for testing
}
gInterface::iButton::iButton(int type, Pos pos, const char* tex, int w, int h) : gameObject(tex, pos, w, h), type(type)
{

}
void gInterface::iButton::restart(Board& brd) {


}

void gInterface::handleEvent(SDL_Event& e)
{
	Pos mpos;
	switch (e.type) {
	case SDL_MOUSEMOTION:


		mpos.x = e.motion.x;
		mpos.y = e.motion.y;

		for (size_t i = 0; i < buttons.size(); i++)
		{
			Pos temp0 = mpos;
			temp0 -= getPos();

			//	std::cout << temp.x << " " << temp.y<< "\n";
			if (buttons[i]->isInside(temp0)) {
				buttons[i]->mark();
			}
			else buttons[i]->unmark();
		}
		//std::cout << mpos.x << " " << mpos.y << "\n";
		if (drag_) {
			this->setPos(mpos);

		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		int x, y;
		SDL_GetMouseState(&x, &y);
		mpos.x = x; mpos.y = y;

		if (e.button.button == SDL_BUTTON_LEFT) {
			if (LMB_STATE == 0) {


				LMB_STATE = true;
				//	std::cout << LMB_STATE << "\n";

				Pos temp0 = mpos;
				temp0 -= getPos();

				if (buttons[0]->isInside(temp0)) {
					brd.Init();
				}
				else if (buttons[1]->isInside(temp0)) {

				}
				else if (buttons[2]->isInside(temp0)) {

				}
				else if (buttons[3]->isInside(temp0)) {

				}
				else if (buttons[4]->isInside(temp0)) {
					brd.togglePiecesAlpha();
				}
				else if (buttons[5]->isInside(temp0)) {
					brd.toggleNumbers();
				}
			}
		}
		if (e.button.button == SDL_BUTTON_RIGHT) {
			if (RMB_STATE == 0) {
				RMB_STATE = 1;
				if (this->isInside(mpos))
					drag_ = true;
			}
		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (e.button.button == SDL_BUTTON_LEFT) {
			if (LMB_STATE == true) {
				LMB_STATE = false;
			}
		}
		if (e.button.button == SDL_BUTTON_RIGHT) {
			if (RMB_STATE == true) {
				RMB_STATE = false;
				drag_ = false;

			}

		}
		break;
	default:
		break;
	}
}

void gInterface::Draw()
{

	for (size_t i = 0; i < buttons.size(); i++)
	{
		Pos buttonRel = buttons[i]->getPos();
		buttonRel += getPos();
		//	std::cout << res.x << " " << res.y << "\n";
		SDL_Color cl;
		if (!buttons[i]->isMarked()) cl = { 240,240,240 };
		else cl = { 255,180,200 };
		gameObject::gfx->DrawRect(cl, buttonRel, buttons[i]->getW(), buttons[i]->getH());
		buttons[i]->Draw(buttonRel);
	}
}
