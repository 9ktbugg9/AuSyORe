#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "AudioMngr.h"
#include "CTexture.h"
#include<cstdio>

class EffectStore {
public:
	SDL_Point pos;
	std::string effect;
};

// TODO: Make an Effect Manager

class TextMngr {
private:
	SDL_Renderer *_renderer;
	SDL_Window *_window;
	AudioMngr *_sounds;

	TTF_Font *chintzy30 = nullptr;
	TTF_Font *chintzy120 = nullptr;

	CTexture _text;

	std::vector<std::string> _dialogueLines;
	std::vector<EffectStore> _effects;
	SDL_Color _textColor = {255, 255, 255};

	std::vector<std::string> _lines, _manipLines;
	std::vector<int> _read;
	std::vector<CTexture> _dispText;
	int _lineAmount = 0, readTime = 0, edgeBuffer = 5, yOffset = 0, yIncrement = 0;
	SDL_Rect _pos, _orgPos, _smooth[2];

	bool _moreLine = false, _continue = false, _continuePrime = false, _skip = false;
	int _lineInc = 0, _skipBufferTime = 0;

	void parseString(std::string, std::string, std::string, std::string &);
	void pEvent(const Uint8 *, SDL_Point, int &);

	void init();
	void setupFont(TTF_Font *, std::string);
	void clean(bool);
public:
	bool reading = false;

	void readFile(int, int, std::string, SDL_Rect &);
	void read(std::string, SDL_Rect &);
	void update(const Uint8 *CKS, SDL_Point mousePos, int &mouseScroll);
	void render();

	TextMngr(SDL_Renderer *, SDL_Window *, AudioMngr *);
	~TextMngr();
};

