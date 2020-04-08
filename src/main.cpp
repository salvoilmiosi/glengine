#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include <iostream>
#include <string>

#include <cmath>
#include <ctime>

#include "engine/engine.h"

int main (int argc, char **argv) {
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "Could not init SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

	engine m_engine;

	int err = m_engine.init();
	if (err != 0) return err;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	SDL_GL_SetSwapInterval(1);

    m_engine.mainLoop();

	SDL_Quit();

    return 0;
}