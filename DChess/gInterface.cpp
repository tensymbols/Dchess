#include "gInterface.h"
#include "Board.h"
gInterface::gInterface(Pos pos_, const char* texfile, Board& brd) : gameObject(texfile, pos_, 96, 32), brd(brd)
{

	buttons.push_back(new iButton(0, pos_, "textures/interface/button0.png", 32, 32));
	buttons.push_back(new iButton(1, { pos_.x + 32, pos_.y }, "textures/interface/button1.png", 32, 32));
	buttons.push_back(new iButton(2, { pos_.x + 64, pos_.y }, "textures/interface/button2.png", 32, 32));
	// hardcoded for testing
}
gInterface::iButton::iButton(int type,Pos pos, const char* tex, int w, int h) : gameObject(tex, pos, w,h), type(type)
{

}
void gInterface::iButton::restart(Board& brd) {

	
}

void gInterface::handleEvent(SDL_Event &e)
{

	switch (e.type) {
	case SDL_MOUSEMOTION:
		Pos mpos;

		mpos.x = e.motion.x;
		mpos.y = e.motion.y;


		for (size_t i = 0; i < buttons.size(); i++)
		{
			if (buttons[i]->isInside(mpos)) {
				buttons[i]->mark();
			}
			else buttons[i]->unmark();
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		
		if (e.button.button == SDL_BUTTON_LEFT) {
			if(LMB_STATE==0){
			

				LMB_STATE = true;
				//	std::cout << LMB_STATE << "\n";
				int x, y;
				SDL_GetMouseState(&x, &y);
				Pos mpos; mpos.x = x; mpos.y = y;


				if (buttons[0]->isInside(mpos)) {
					brd.Init();
				}
				
			}
		}
		if (e.button.button == SDL_BUTTON_RIGHT) {

		}
		break;
	case SDL_MOUSEBUTTONUP:
		if (e.button.button == SDL_BUTTON_LEFT) {
			if (LMB_STATE == true) {
				LMB_STATE = false;
			}
		}
		if (e.button.button == SDL_BUTTON_RIGHT) {

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
		Pos temp = buttons[i]->getPos();
		SDL_Color cl;
		if (!buttons[i]->isMarked()) cl = { 240,240,240 };
		else cl = { 240,200,200 };
		gameObject::gfx->DrawRect(cl, { temp.x + 2,temp.y + 2 }, buttons[i]->getW() - 4, buttons[i]->getH() - 4);
		buttons[i]->Draw();
	}
}
