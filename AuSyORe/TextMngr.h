#pragma once
#include "SDL.h"
#include <vector>
#include <fstream>
#include <sstream>
#include "CTexture.h"


class TextMngr {
private:
	SDL_Renderer *_renderer;
	SDL_Window *_window;

	TTF_Font *chintzy30 = nullptr;

	CTexture _text;

	std::vector<std::string> _lines, _manipLines;
	std::vector<int> _read;
	std::vector<CTexture> _dispText;
	int _lineAmount = 0, readTime = 0, edgeBuffer = 5, yOffset = 0, yIncrement = 23;
	SDL_Rect _pos, _orgPos;

	void init();
	void setupFont(TTF_Font *, std::string);
	void clean(bool);
public:
	bool reading = false;

	void read(std::string, int, SDL_Rect &);
	void pEvent(const Uint8 *);
	void update();
	void render();

	TextMngr(SDL_Renderer *, SDL_Window *);
	~TextMngr();
};

// Render text one letter at a time by creating full texture, then only rendering current letters. 