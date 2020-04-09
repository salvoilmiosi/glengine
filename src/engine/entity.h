#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "context.h"

class entity {
public:
    virtual void tick(context *con) {}
    virtual void render(context *con) {}
};

#endif // __ENTITY_H__