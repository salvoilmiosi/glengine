#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <SDL2/SDL.h>

#include "context.h"

class engine {
public:
    engine();
    ~engine();

public:
    void mainLoop();

    virtual void tick() = 0;
    virtual void render() = 0;

    context *getContext() {
        return &con;
    }

private:
    context con;
};

#endif // __ENGINE_H__