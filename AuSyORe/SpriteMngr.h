#pragma once
#include "SDL.h"
#include <vector>
#include "CTexture.h"

class SpriteMngr {
private:
	SDL_Renderer *_renderer;
	SDL_Window *_window;

public:



	SpriteMngr(SDL_Renderer *, SDL_Window *);
	~SpriteMngr();
};

