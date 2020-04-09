#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "engine/model.h"
#include "engine/shader.h"
#include "engine/vertex_array.h"

#include <glm/glm.hpp>

class triangle : public model {
public:
    triangle();
    ~triangle();

public:
    void tick();
    void render();

private:
    vertex_array vao;
    
    glm::vec3 color;
    glm::mat4 model_matrix = glm::mat4(1.0);
    glm::mat4 view_matrix = glm::mat4(1.0);

    shader program;
};

#endif // __TRIANGLE_H__