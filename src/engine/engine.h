#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <SDL2/SDL.h>

#include <set>

#include "context.h"
#include "entity.h"

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

    void add_entity(entity *ent) {
        entities.insert(ent);
    }

    void remove_entity(entity *ent) {
        entities.erase(ent);
    }

private:
    context con;

    std::set<entity *> entities;
};

#endif // __ENGINE_H__