#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include <iostream>
#include <string>

#include <cmath>
#include <ctime>

#include "engine/engine.h"

#include "triangle.h"

int main (int argc, char **argv) {
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "Could not init SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    try {
	    engine m_engine;
        triangle t;

        m_engine.add_model(&t);
        m_engine.mainLoop();
    } catch (const std::string &error) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error.c_str(), nullptr);
        std::cerr << error << std::endl;
        return -2;
    }

	SDL_Quit();

    return 0;
}