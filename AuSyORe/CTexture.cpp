#include "stdafx.h"
#include "CTexture.h"

SDL_Window CTexture::*mWindow = nullptr;

bool CTexture::loadFromFile(std::string path) {
	free();
	_path = path;
	SDL_Texture* newTexture = nullptr;

	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == nullptr)
		std::cout << "-Unable to Load Image- Reason: " << IMG_GetError() << "  -Path: " << path.c_str() << std::endl;
	else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0x00, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(_renderer, loadedSurface);
		if (newTexture == nullptr)
			std::cout << "-Unable to Create Texture- Reason: " << SDL_GetError() << "  -Path: " << path.c_str() << std::endl;
		else {
			_width = loadedSurface->w;
			_height = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	_texture = newTexture;
	return _texture != nullptr;
}

bool CTexture::loadFromText(std::string textureText, SDL_Color textColor, TTF_Font *font) {
	free();

	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface == nullptr) std::cout << "-Unable to Create Surface Text- Reason: " << TTF_GetError() << std::endl;
	else {
		_texture = SDL_CreateTextureFromSurface(_renderer, textSurface);
		if (_texture == nullptr) std::cout << "-Unable to Create Texture Text- Reason: " << TTF_GetError() << std::endl;
		else {
			_width = textSurface->w;
			_height = textSurface->h;
		}
		SDL_FreeSurface(textSurface);
	}
	return _texture != nullptr;
}

void CTexture::free() {
	if (_texture != nullptr) {
		SDL_DestroyTexture(_texture);
		_texture = nullptr;
		_width = _height = 0;
	}
}

void CTexture::render(int x, int y, SDL_Rect* clip, double scaleW, double scaleH, int sW, int sH, double angle, SDL_Point center, SDL_RendererFlip flip) {
	SDL_Rect renderQuad = {x, y, _width, _height};
	if (scaleW == 0)
		scaleW = 1;
	if (scaleH == 0)
		scaleH = 1;
	if (clip != nullptr) {
		if (sW != 0 && sH != 0) {
			renderQuad.w = sW;
			renderQuad.h = sH;
		}
		else {
			renderQuad.w = clip->w;
			renderQuad.h = clip->h;
			renderQuad.w *= static_cast<int>(scaleW);
			renderQuad.h *= static_cast<int>(scaleH);
		}
	}
	SDL_RenderCopyEx(_renderer, _texture, clip, &renderQuad, angle, &center, flip);
}

void CTexture::render(int x, int y, SDL_Rect *pos, SDL_Renderer *rend) {
	SDL_Rect renderQuad = {x, y, _width, _height};

	SDL_RenderCopy(rend, _texture, &renderQuad, pos);
}