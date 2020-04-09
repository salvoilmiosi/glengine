#ifndef __VERTEX_ARRAY_H__
#define __VERTEX_ARRAY_H__

#include <GL/glew.h>
#include <GL/gl.h>
#include <initializer_list>

enum attrib_type {
    ATTR_BYTE,
    ATTR_UNSIGNED_BYTE,
    ATTR_SHORT,
    ATTR_UNSIGNED_SHORT,
    ATTR_INT,
    ATTR_UNSIGNED_INT,
    ATTR_FLOAT,
    ATTR_DOUBLE,
    ATTR_VEC2,
    ATTR_VEC3,
    ATTR_VEC4
};

enum draw_mode {
    DRAW_POINTS,
    DRAW_LINES,
    DRAW_TRIANGLES,
    DRAW_TRIANGLE_STRIP,
    DRAW_TRIANGLE_FAN
};

struct vertex_attrib {
    int location;
    attrib_type type;
};

class vertex_array {
public:
    vertex_array(draw_mode mode, size_t num_vbos = 1);
    ~vertex_array();

    void update_vertices(size_t vbo_index, const void *data, const size_t size, std::initializer_list<vertex_attrib> attribs, bool dynamic = false);
    void update_indices(const unsigned int *data, const size_t size, bool dynamic = false);
    void draw();

private:
    const size_t num_vbos;
    
    GLuint gl_vao;
    GLuint *gl_vbo;
    GLuint gl_ebo;

    GLenum gl_draw_mode;

    size_t index_count;
};

#endif // __VERTEX_ARRAY_H__