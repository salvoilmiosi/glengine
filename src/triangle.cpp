#include "triangle.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

static const char *vertex_source =
"#version 330 \n"
"layout (location = 0) in vec3 position; \n"
"layout (location = 1) in vec3 color; \n"
"out vec3 vec_color; \n"
"uniform mat4 model_matrix;\n"
"uniform mat4 view_matrix;\n"
"void main() { \n"
"   gl_Position = view_matrix * model_matrix * vec4(position, 1.0); \n"
"   vec_color = color; \n"
"} \n";

static const char *fragment_source =
"#version 330 \n"
"out vec4 FragColor; \n"
"in vec3 vec_color;\n"
"uniform vec3 color;\n"
"void main() { \n"
"   FragColor = vec4(mix(vec_color, color, 0.05), 1.0); \n"
"} \n";

struct vertex {
    glm::vec3 position;
    glm::vec3 color;
};

triangle::triangle() : 
    vao(DRAW_TRIANGLES),
    program("triangle", vertex_source, fragment_source)
{
    program.add_uniform("color", &color);
    program.add_uniform("model_matrix", &model_matrix);
    program.add_uniform("view_matrix", &view_matrix);

    const vertex vertices[] = {
        {{-0.5f, -0.5f, 0.0f}, {1.f, 0.f, 0.f}},
        {{ 0.5f, -0.5f, 0.0f}, {0.f, 1.f, 0.f}},
        {{ 0.0f,  0.5f, 0.0f}, {0.f, 0.f, 1.f}},
    };

    const unsigned int elements[] = {
        0, 1, 2
    };

    vao.update_vertices(0, vertices, sizeof(vertices), {{0, ATTR_VEC3}, {1, ATTR_VEC3}});
    vao.update_indices(elements, sizeof(elements));

    view_matrix = glm::rotate(view_matrix, 0.2f, glm::vec3(1.f, 0.f, 0.f));
}

triangle::~triangle() {

}

void triangle::tick() {
    color = {(rand() % 255) / 255.f, (rand() % 255) / 255.f, (rand() % 255) / 255.f};

    model_matrix = glm::rotate(model_matrix, 0.02f, glm::vec3(0.f, 1.f, 0.f));
}

void triangle::render() {
    program.use_program();
    vao.draw();
}