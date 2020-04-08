#include "model.h"

#include <glm/glm.hpp>

model::model() {
    glCreateVertexArrays(1, &gl_vao);
    glBindVertexArray(gl_vao);

    glm::vec3 vertices[] = {
        {-0.5f, -0.5f, 0.0f},
        { 0.5f, -0.5f, 0.0f},
        { 0.0f,  0.5f, 0.0f},
    };

    glCreateBuffers(1, &gl_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, gl_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, 0, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

model::~model() {
    glDeleteVertexArrays(1, &gl_vao);
    glDeleteBuffers(1, &gl_vbo);
}

void model::render() {
    glBindVertexArray(gl_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}