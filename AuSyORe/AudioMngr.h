#pragma once
#include <iostream>
#include "SDL_mixer.h"


class AudioMngr {
public:
	Mix_Chunk *text = NULL;

	AudioMngr();
	~AudioMngr();

private:
};

