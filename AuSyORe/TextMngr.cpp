#include "stdafx.h"
#include "TextMngr.h"


TextMngr::TextMngr(SDL_Renderer *rendSrc, SDL_Window *windSrc, AudioMngr *soundSrc) : _renderer(rendSrc), _window(windSrc), _sounds(soundSrc) {
	init();

	_text.setSpecs(_renderer, _window);

}

void TextMngr::update() {
	if (reading) {
		readTime++;
		if (readTime > 1) {
			Mix_PlayChannel(1, _sounds->text, 0);
			readTime = 0;
			for (int i = 0; i < _lineAmount; i++) {
				if (_read[i] == _lines[i].length() || _read[i] == -1) continue;
				std::string temp = _lines[i];
				_manipLines[i].push_back(temp[_read[i]++]);
				if (_read[i] == _lines[i].length() && i < _lineAmount - 1) _read[i + 1] = 0;
			}
			SDL_Color textColor = {255, 255, 255};
			for (int i = 0; i < _lineAmount; i++)
				if (_read[i] != -1 && _read[i] <= _lines[i].length()) {
					_dispText[i].loadFromText(_manipLines[i], textColor, chintzy30);
				}

			bool brk = false;
			for (int i = 0; i < _lineAmount; i++) if (_manipLines[i].length() < _lines[i].length()) brk = true;
			if (!brk) { reading = false; clean(false); }
		}
	}
}

void TextMngr::render() {
	for (int i = 0; i < _lineAmount; i++) {
		int x = _pos.x + edgeBuffer;
		int y = _pos.y + edgeBuffer + (i * yIncrement) + yOffset;
		if (_pos.y + _pos.h + 27 > y + _dispText[i].getHeight() && y > _pos.y + edgeBuffer - 1 - 27)
			_dispText[i].render(x, y);
	}
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	for (int i = 0; i < 2; i++) SDL_RenderFillRect(_renderer, &_smooth[i]);

	SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
	SDL_RenderDrawRect(_renderer, &_pos);
}

void TextMngr::pEvent(SDL_Point mousePos, int &mouseScroll) {
	bool outside = false;
	if (_pos.y + _pos.h <= mousePos.y) outside = true;
	if (_pos.y >= mousePos.y) outside = true;
	if (_pos.x + _pos.w <= mousePos.x) outside = true;
	if (_pos.x >= mousePos.x) outside = true;

	if (!outside) {
		if (mouseScroll > 0) if (_pos.y + yOffset < _orgPos.y + edgeBuffer) yOffset += 20;
		if (mouseScroll < 0) if (_pos.y + yOffset - _orgPos.h > _orgPos.y - yIncrement * (_lineAmount + 1)) yOffset -= 20;
	}
	if (mouseScroll != 0) mouseScroll = 0;
}

void TextMngr::read(std::string dir, int line, SDL_Rect &pos) {
	clean(true);
	reading = true;
	_pos = _orgPos = pos;
	_smooth[0] = {_pos.x + 1, _pos.y + 1 - 27, _pos.w - 2, 27};
	_smooth[1] = {_pos.x + 1, _pos.y + _pos.h, _pos.w - 2, 27};

	std::string start = dir;

	SDL_Color textColor = {0, 0, 0};
	_text.loadFromText(start, textColor, chintzy30);


	std::vector<std::string> words;
	std::stringstream ssin(start);
	while (ssin.good()) {
		std::string temp;
		ssin >> temp;
		words.push_back(temp);
	}

	std::string testing;

	int inc = 0;
	_lines.push_back(words[0] + " ");
	for (int i = 1; i < words.size(); i++) {
		std::string temp = _lines[inc];
		temp.append(words[i]);
		_text.loadFromText(temp, textColor, chintzy30);
		if (_text.getWidth() >= pos.w - edgeBuffer) { inc++; _lines.push_back(words[i] + " "); }
		else if (i == words.size() - 1) _lines[inc].append(words[i]);
		else _lines[inc].append(words[i] + " ");
	}
	inc++;
	_lines.push_back("    Continue...");

	_read.push_back(0);
	for (int i = 0; i < inc; i++)  _read.push_back(-1);
	for (int i = 0; i <= inc; i++)  _manipLines.push_back("");
	for (int i = 0; i <= inc; i++) { _dispText.push_back(CTexture()); _dispText[i].setSpecs(_renderer, _window); };
	_lineAmount = _read.size();
}


void TextMngr::clean(bool full) {
	if (full) {
		_dispText.clear();
		_lineAmount = 0;
	}
	_manipLines.clear();
	_lines.clear();
	_read.clear();
	_text.free();
}

void TextMngr::init() {
	if (TTF_Init() == -1) std::cout << "-TTF Error- Reason: " << TTF_GetError() << std::endl;

	chintzy30 = TTF_OpenFont("res/fonts/chintzy.ttf", 30);
	if (chintzy30 == NULL) std::cout << "-Failed to Load Font \"chintzy30\"- Reason: " << TTF_GetError() << std::endl;

	std::ifstream test("res/fonts/chintzy30.txt");
	if (!test.is_open()) setupFont(chintzy30, "chintzy30");
	test.close();
}

void TextMngr::setupFont(TTF_Font *font, std::string name) {
	std::string nameDir = "res/fonts/";
	std::ofstream fout(nameDir.append(name + ".txt").c_str());

	SDL_Color cl{0, 0, 0};
	CTexture temp;
	temp.setSpecs(_renderer, _window);
	for (int i = 33; i <= 126; i++) {
		std::string ch = "";
		ch.push_back(char(i));
		temp.loadFromText(ch, cl, font);
		fout << char(i) << " = " << i << " = " << temp.getWidth() << "-" << temp.getHeight() << std::endl;
	}

	temp.free();
	fout.close();
}

TextMngr::~TextMngr() {
	clean(true);
	TTF_CloseFont(chintzy30);

	TTF_Quit();
}
