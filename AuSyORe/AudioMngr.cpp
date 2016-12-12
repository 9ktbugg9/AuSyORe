#include "stdafx.h"
#include "AudioMngr.h"


AudioMngr::AudioMngr() {
	if (Mix_OpenAudio(105000, MIX_DEFAULT_FORMAT, 2, 4096)  < 0)
		std::cout << "-SDL_Mixer Error- Reason: " << Mix_GetError() << std::endl;

	text = Mix_LoadWAV("res/sounds/click1.wav");

}


AudioMngr::~AudioMngr() {
	Mix_FreeChunk(text);

	Mix_Quit();
}
