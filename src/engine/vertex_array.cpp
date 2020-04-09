#include "vertex_array.h"

static constexpr struct {
    GLint num;
    GLenum type;
    GLenum size;
} attrib_gl_info[] = {
    {1, GL_BYTE, sizeof(char)},
    {1, GL_UNSIGNED_BYTE, sizeof(char)},
    {1, GL_SHORT, sizeof(short)},
    {1, GL_UNSIGNED_SHORT, sizeof(short)},
    {1, GL_INT, sizeof(int)},
    {1, GL_UNSIGNED_INT, sizeof(int)},
    {1, GL_FLOAT, sizeof(float)},
    {1, GL_DOUBLE, sizeof(double)},
    {2, GL_FLOAT, 2 * sizeof(float)},
    {3, GL_FLOAT, 3 * sizeof(float)},
    {4, GL_FLOAT, 4 * sizeof(float)}
};

static constexpr GLenum gl_draw_modes[] = {
    GL_POINTS,
    GL_LINES,
    GL_TRIANGLES,
    GL_TRIANGLE_STRIP,
    GL_TRIANGLE_FAN
};

vertex_array::vertex_array(draw_mode mode, size_t num_vbos) :
    num_vbos(num_vbos),
    gl_draw_mode(gl_draw_modes[mode])
{
    gl_vbo = new GLuint[num_vbos];
    glGenVertexArrays(1, &gl_vao);
    glGenBuffers(num_vbos, gl_vbo);
    glGenBuffers(1, &gl_ebo);
}

vertex_array::~vertex_array() {
    glDeleteVertexArrays(1, &gl_vao);
    glDeleteBuffers(num_vbos, gl_vbo);
    glDeleteBuffers(1, &gl_ebo);
    delete[] gl_vbo;
}

void vertex_array::update_vertices(size_t vbo_index, const void *data, const size_t size, std::initializer_list<vertex_attrib> attribs, bool dynamic) {
    glBindVertexArray(gl_vao);
    glBindBuffer(GL_ARRAY_BUFFER, gl_vbo[vbo_index]);
    glBufferData(GL_ARRAY_BUFFER, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);

    GLsizei stride = 0;
    for (auto &a : attribs) {
        stride += attrib_gl_info[a.type].size;
    }

    size_t start = 0;
    for (auto &a : attribs) {
        glVertexAttribPointer(a.location, attrib_gl_info[a.type].num, attrib_gl_info[a.type].type, GL_FALSE, stride, (void *)start);
        start += attrib_gl_info[a.type].size;
        glEnableVertexAttribArray(a.location);
    }

    glBindVertexArray(0);
}

void vertex_array::update_indices(const unsigned int *data, const size_t size, bool dynamic) {
    glBindVertexArray(gl_vao);
    index_count = size / sizeof(unsigned int);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gl_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void vertex_array::draw() {
    glBindVertexArray(gl_vao);
    glDrawElements(gl_draw_mode, index_count, GL_UNSIGNED_INT, (void *)0);
    glBindVertexArray(0);
}