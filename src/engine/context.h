#ifndef __CONTEXT_H__
#define __CONTEXT_H__

#include <SDL2/SDL.h>
#include <Gl/glew.h>

struct context {
    SDL_Window *window = nullptr;
    
    const char *window_title = "GL engine";
    int window_width = 800;
    int window_height = 600;
    int tickrate = 5;
};

#endif // __CONTEXT_H__