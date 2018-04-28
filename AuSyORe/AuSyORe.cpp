// Copyright 2016 9ktbugg9, All rights reserved.
// AuSyORe - Automated System of Recovery
#include "stdafx.h"
#include "SDL.h"

#include "Game.h"


int SDL_main(int argc, char* argv[]) {
	srand(unsigned(time(nullptr)));

	try {
		Game game;
		game.startLoop();
	}
	catch (int exeption) {
		std::cout << "An exception has occured ~ Error code: " << exeption << std::endl;
		system("pause");
	}

	return 0;
}

