#pragma once
#include <ctime>
#include <random>

#include "Window.h"
#include "SpriteMngr.h"
#include "AudioMngr.h"

#define WINDOW_NAME "AuSyORe"
#define FPS 60

class Game {
	Window *window;
	AudioMngr *sounds;
	SpriteMngr *sprites;

	Uint32 startingTick, fpsTick;
	int myFPS;

	void init();

	void updateAll();
	void renderAll();
	void manageFPS();
public:

	void startLoop();

	Game() { init(); };
	~Game();
};

