#include "engine.h"

#include <iostream>

#include <GL/glew.h>
#include <GL/gl.h>

engine::engine() {

}

engine::~engine() {
	SDL_DestroyWindow(con.window);
}

int engine::init() {
    Uint32 winflags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;
    con.window = SDL_CreateWindow(con.window_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, con.window_width, con.window_height, winflags);

    if (!con.window) {
        std::cerr << "Could not create SDL Window: " << SDL_GetError() << std::endl;
        return -2;
    }

    SDL_GLContext glcontext = SDL_GL_CreateContext(con.window);
    if (!glcontext) {
        std::cerr << "Could not create OpenGL Context: " << SDL_GetError() << std::endl;
        return -3;
    }
    
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	glewExperimental = true;
	GLenum error = glewInit();
	if (error != GLEW_OK) {
        std::cerr << "Could not init glew: error " << error << std::endl;
		return -4;
	}

    return 0;
}

void engine::mainLoop() {
	SDL_Event event;

	std::string fpsCounter;

	int lastTime = SDL_GetTicks();
	float unprocessed = 0;
	float msPerTick = 1000.f / con.tickrate;
	int frames = 0;
	int ticks = 0;
	int secondsTimer = SDL_GetTicks();

	bool quit = false;
	while (!quit) {
		int now = SDL_GetTicks();
		unprocessed += (now - lastTime) / msPerTick;
		lastTime = now;
		bool shouldRender = false;
		while (unprocessed >= 1) {
			tick();

			++ticks;
			--unprocessed;
			shouldRender = true;
		}

		if (shouldRender) {
			render();

			SDL_GL_SwapWindow(con.window);

			++frames;
		}

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					quit = true;
				}
				break;
			}
		}

		if (SDL_GetTicks() - secondsTimer > 1000) {
			secondsTimer += 1000;
			fpsCounter = std::string(con.window_title) + " Frames: " + std::to_string(frames) + " Ticks: " + std::to_string(ticks);
			SDL_SetWindowTitle(con.window, fpsCounter.c_str());
			frames = 0;
			ticks = 0;
		}
	}
}

void engine::tick() {
	
}

void engine::render() {

}