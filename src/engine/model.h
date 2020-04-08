#ifndef __MODEL_H__
#define __MODEL_H__

#include <GL/glew.h>
#include <GL/gl.h>

#include "shader.h"

class model {
public:
    model();
    ~model();

public:
    void render();

private:
    GLuint gl_vao;
    GLuint gl_vbo;
};

#endif // __MODEL_H__