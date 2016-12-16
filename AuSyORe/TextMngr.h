#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "AudioMngr.h"
#include "CTexture.h"
#include<cstdio>

class TextMngr {
private:
	SDL_Renderer *_renderer;
	SDL_Window *_window;
	AudioMngr *_sounds;

	TTF_Font *chintzy30 = nullptr;

	CTexture _text;

	std::vector<std::string> _dialogueLines;

	std::vector<std::string> _lines, _manipLines;
	std::vector<int> _read;
	std::vector<CTexture> _dispText;
	int _lineAmount = 0, readTime = 0, edgeBuffer = 5, yOffset = 0, yIncrement = 23;
	SDL_Rect _pos, _orgPos, _smooth[2];

	bool _moreLine = false, _continue = false, _continuePrime = false;
	int _lineInc = 0;

	void parseString(std::string, std::string, std::string, std::string &);

	void init();
	void setupFont(TTF_Font *, std::string);
	void clean(bool);
public:
	bool reading = false;

	void read(int, int, std::string, SDL_Rect &);
	void read(std::string, SDL_Rect &);
	void pEvent(const Uint8 *, SDL_Point, int &);
	void update();
	void render();

	TextMngr(SDL_Renderer *, SDL_Window *, AudioMngr *);
	~TextMngr();
};

