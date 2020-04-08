#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <GL/gl.h>

#include <iostream>
#include <string>

#include <cmath>
#include <ctime>

#include "engine/engine.h"
#include "engine/shader.h"
#include "engine/model.h"

const char *vertex_source =
"#version 330 \n"
"layout (location = 0) in vec3 position; \n"
"void main() { \n"
"   gl_Position = vec4(position, 1.0); \n"
"} \n";
const char *fragment_source =
"#version 330 \n"
"out vec4 FragColor; \n"
"uniform vec3 color;"
"void main() { \n"
"   FragColor = vec4(color, 1.0); \n"
"} \n";

glm::vec3 triangle_color = {0.f, 0.f, 1.f};

class game_engine : public engine {
public:
    void tick() {
        triangle_color = {(rand() % 255) / 255.f, (rand() % 255) / 255.f, (rand() % 255) / 255.f};
    }

    void render() {
        program->use_program();
        triangle->render();
    }

public:
    model *triangle;
    shader *program;
};

int main (int argc, char **argv) {
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        std::cerr << "Could not init SDL: " << SDL_GetError() << std::endl;
        return -1;
    }

    try {
	    game_engine m_engine;

        SDL_GL_SetSwapInterval(1);

        shader program("triangle", vertex_source, fragment_source);
        program.add_uniform("color", &triangle_color);

        model triangle;
        m_engine.triangle = &triangle;
        m_engine.program = &program;

        m_engine.mainLoop();
    } catch (const std::string &error) {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", error.c_str(), nullptr);
        std::cerr << error << std::endl;
        return -2;
    }

	SDL_Quit();

    return 0;
}