#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <SDL2/SDL.h>

#include <set>

#include "context.h"
#include "model.h"

class engine {
public:
    engine();
    ~engine();

public:
    void mainLoop();

    void tick();
    void render();

    context *getContext() {
        return &con;
    }

    void add_model(model *mod) {
        models.insert(mod);
    }

    void remove_model(model *mod) {
        models.erase(mod);
    }

private:
    context con;

    std::set<model *> models;
};

#endif // __ENGINE_H__