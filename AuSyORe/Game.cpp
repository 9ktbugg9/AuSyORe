#include "stdafx.h"
#include "Game.h"

void Game::startLoop() {

	texts->readFile(0, 9 + 7, "res/dialogue/temp.txt", tempPos);

	while (true) {
		startingTick = SDL_GetTicks(); myFPS++;

		if (!window->pEvents(mouseScroll)) break; // Handling Window events

		updateAll(); // Update the game
		renderAll(); // Render the game
		manageFPS(); // Manage the FPS
	}
}

void Game::updateAll() {

	const Uint8 *CKS = SDL_GetKeyboardState(nullptr);
	int mouseX, mouseY;
	const Uint16 CMS = SDL_GetMouseState(&mouseX, &mouseY);
	SDL_Point mousePos{mouseX, mouseY};

	texts->update(CKS, mousePos, mouseScroll);
}

void Game::renderAll() {
	SDL_SetRenderDrawColor(window->_renderer, 0, 0, 0, 0);
	SDL_RenderClear(window->_renderer);

	texts->render();
	
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
	sprites = new SpriteMngr(window->_renderer, window->_window);
	sounds = new AudioMngr;
	texts = new TextMngr(window->_renderer, window->_window, sounds);

	startingTick, fpsTick = SDL_GetTicks();
	myFPS = 0;
}


Game::~Game() {
	delete(texts); texts = nullptr;
	delete(sprites); sprites = nullptr;
	delete(sounds); sounds = nullptr;
	delete(window); window = nullptr;
}
