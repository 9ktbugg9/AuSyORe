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
	std::string pass1 = "The central problems (or goals) of AI research include reasoning, knowledge, planning, learning, natural language processing, perception and the ability to move and manipulate objects. General intelligence is among the field's goals. Approaches include statistical methods, computational intelligence, soft computing, and traditional symbolic AI. Many tools are used, including versions of search and mathematical optimization, logic, methods based on probability and economics. The AI field draws upon computer science, mathematics, psychology, philosophy, neuroscience and artificial psychology.";
	std::string pass2 = "A rainbow is a meteorological phenomenon that is caused by reflection, refraction and dispersion of light in water droplets resulting in a spectrum of light appearing in the sky. It takes the form of a multicoloured arc. Rainbows caused by sunlight always appear in the section of sky directly opposite the sun.";
	if (!tempText) { texts->read(pass1, 0, tempPos); tempText = true; }
	const Uint8 *CKS = SDL_GetKeyboardState(nullptr);
	if(CKS[SDL_SCANCODE_E]) texts->read(pass2, 0, tempPos);
	texts->pEvent(CKS);
	texts->update();
}

void Game::renderAll() {
	SDL_SetRenderDrawColor(window->_renderer, 0, 0, 0, 0);
	SDL_RenderClear(window->_renderer);

	// Render Stuff Here
	SDL_SetRenderDrawColor(window->_renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(window->_renderer, &tempPos);
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
	texts = new TextMngr(window->_renderer, window->_window);
	sounds = new AudioMngr;

	startingTick, fpsTick = SDL_GetTicks();
	myFPS = 0;

	SDL_SetRenderDrawColor(window->_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
}


Game::~Game() {
	delete(texts); texts = nullptr;
	delete(sprites); sprites = nullptr;
	delete(sounds); sounds = nullptr;
	delete(window); window = nullptr;
}
