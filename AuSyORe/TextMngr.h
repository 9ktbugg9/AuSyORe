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
public:
	bool reading = false;

	void readFile(int, int, std::string, SDL_Rect &);
	void read(std::string, SDL_Rect &);

	void update(const Uint8 *CKS, SDL_Point mousePos, int &mouseScroll);
	void render();

	TextMngr(SDL_Renderer *, SDL_Window *, AudioMngr *);
	~TextMngr();

private:
	SDL_Renderer *_renderer;
	SDL_Window *_window;
	AudioMngr *_sounds;

	TTF_Font *chintzy30 = nullptr;
	TTF_Font *chintzy120 = nullptr;

	CTexture _text;
	SDL_Color _textColor = {255, 255, 255};
	SDL_Rect _pos, _orgPos, _smooth[2];

	std::vector<std::string> _dialogueLines, _lines, _manipLines;
	std::vector<EffectStore> _effects;
	std::vector<CTexture> _dispText;
	std::vector<int> _read;


	int _lineAmount = 0, _readTime = 0, _edgeBuffer = 5, _yOffset = 0,
		_yIncrement = 0, _lineInc = 0, _skipBufferTime = 0;

	bool _moreLine = false, _continue = false, _continuePrime = false,
		 _skip = false;


	void parseString(std::string, std::string, std::string, std::string &);
	void pEvent(const Uint8 *, SDL_Point, int &);

	void setupFont(TTF_Font *, std::string);
	void init();
	void clean(bool);
};

