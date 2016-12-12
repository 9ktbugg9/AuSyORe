#pragma once
#include <ctime>
#include <random>

#include "Window.h"
#include "SpriteMngr.h"
#include "AudioMngr.h"
#include "TextMngr.h"

#define WINDOW_NAME "AuSyORe"
#define FPS 60

class Game {
	Window *window;
	AudioMngr *sounds;
	SpriteMngr *sprites;
	TextMngr *texts;

	Uint32 startingTick, fpsTick;
	int myFPS;

	void init();

	void updateAll();
	void renderAll();
	void manageFPS();

	int mouseScroll = 0;
	bool tempText = false;
	SDL_Rect tempPos = {20, 20, 820, 250};
public:

	void startLoop();

	Game() { init(); };
	~Game();
};
