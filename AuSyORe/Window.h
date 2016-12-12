#pragma once
#include "SDL.h"
#include "SDL_mixer.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <iostream>
#include "CTexture.h"

using namespace std;

class Window {
private:
	void close();
	bool init(string);
	int SCREEN_WIDTH, SCREEN_HEIGHT;

public:

	SDL_Texture* loadTexture(string path);

	SDL_Window* _window = NULL;
	SDL_Renderer* _renderer = NULL;

	bool pEvents(int &);

	int getWidth() { return SCREEN_WIDTH; }
	int getHeight() { return SCREEN_HEIGHT; }


	Window(string winName) { init(winName); }
	~Window() { close(); }
};

