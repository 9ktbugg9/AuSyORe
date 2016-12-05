#include "stdafx.h"
#include "SpriteMngr.h"


SpriteMngr::SpriteMngr(SDL_Renderer *src, SDL_Window *win) :_renderer(src), _window(win) {
	icon.setSpecs(_renderer, _window);
	icon.loadFromFile("res/icon.png");
}


SpriteMngr::~SpriteMngr() {
	icon.free();
}
