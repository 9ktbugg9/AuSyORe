// Copyright 2016 9ktbugg9, All rights reserved.
// AuSyORe - Automated System of Recovery
#include "stdafx.h"
#include <ctime>
#include <random>

#include "Window.h"
#include "SpriteMngr.h"
#include "AudioMngr.h"

#define WINDOW_NAME "AuSyORe"
#define FPS 60

int main(int args, char* argc[]) {
	srand(unsigned(time(nullptr)));

	Window window(WINDOW_NAME);
	AudioMngr sounds;
	SpriteMngr sprites(window._renderer, window._window);

	Uint32 startingTick, fpsTick = SDL_GetTicks();
	int myFPS = 0;

	while (true) {	// GAME LOOP
		startingTick = SDL_GetTicks(); myFPS++;	

		if (!window.pEvents()) break; // Handling Window events

		SDL_SetRenderDrawColor(window._renderer, 0xFF, 0xFF, 0xFF, 0xFF);

		// Render Stuff Here

		SDL_RenderPresent(window._renderer);

		// Getting current FPS
		if (SDL_GetTicks() > fpsTick + 1000) {
			fpsTick = SDL_GetTicks();
			myFPS = 0;
		}
		// Regulating FPS
		if ((1000 / FPS) > SDL_GetTicks() - startingTick)
			SDL_Delay(1000 / FPS - (SDL_GetTicks() - startingTick));
	}
	return 0;
}

