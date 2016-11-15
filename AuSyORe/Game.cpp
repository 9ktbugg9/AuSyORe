#include "stdafx.h"
#include "Game.h"

void Game::startLoop() {
	while (true) {
		startingTick = SDL_GetTicks(); myFPS++;

		if (!window->pEvents()) break; // Handling Window events

		updateAll(); // Update the game
		renderAll(); // Render the game
		manageFPS(); // Manage the FPS
	}
}

void Game::updateAll() {
	// Update Stuff Here
}

void Game::renderAll() {

	// Render Stuff Here

	SDL_RenderPresent(window->_renderer);
}

void Game::manageFPS() {
	// Getting current FPS
	if (SDL_GetTicks() > fpsTick + 1000) {
		fpsTick = SDL_GetTicks();
		myFPS = 0;
	}
	// Regulating FPS
	if ((1000 / FPS) > SDL_GetTicks() - startingTick)
		SDL_Delay(1000 / FPS - (SDL_GetTicks() - startingTick));
}

void Game::init() {
	window = new Window(WINDOW_NAME);
	sounds = new AudioMngr;
	sprites = new SpriteMngr(window->_renderer, window->_window);

	Uint32 startingTick, fpsTick = SDL_GetTicks();
	myFPS = 0;

	SDL_SetRenderDrawColor(window->_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}


Game::~Game() {
	delete(sprites);
	delete(sounds);
	delete(window);
}
