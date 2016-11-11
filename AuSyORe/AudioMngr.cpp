#include "stdafx.h"
#include "AudioMngr.h"


AudioMngr::AudioMngr() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
		std::cout << "-SDL_Mixer Error- Reason: " << Mix_GetError() << std::endl;

	//sound = Mix_LoadWAV("sounds/sound.wav");

}


AudioMngr::~AudioMngr() {
	//Mix_FreeChunk(sound);

	Mix_Quit();
}
