#pragma once
#include "SDL.h"
#include <vector>
#include "CTexture.h"

class SpriteMngr {
public:

	SpriteMngr(SDL_Renderer *, SDL_Window *);
	~SpriteMngr();

private:
	SDL_Renderer *_renderer;
	SDL_Window *_window;

	CTexture icon;
};

