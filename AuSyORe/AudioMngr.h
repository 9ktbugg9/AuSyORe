#pragma once
#include <iostream>
#include "SDL_mixer.h"


class AudioMngr {
private:


public:
	Mix_Chunk *text = NULL;

	AudioMngr();
	~AudioMngr();
};

