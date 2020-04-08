#include "shader.h"

#include <iostream>

shader::shader(const char *name, const std::string &vertex_src, const std::string &fragment_src) : name(name) {
	gl_programid = glCreateProgram();

	gl_vertexid = glCreateShader(GL_VERTEX_SHADER);
	compile(gl_vertexid, vertex_src);
	glAttachShader(gl_programid, gl_vertexid);

	gl_fragmentid = glCreateShader(GL_FRAGMENT_SHADER);
	compile(gl_fragmentid, fragment_src);
	glAttachShader(gl_programid, gl_fragmentid);

	glLinkProgram(gl_programid);
}

shader::~shader() {
	glDetachShader(gl_programid, gl_vertexid);
	glDetachShader(gl_programid, gl_fragmentid);
	glDeleteShader(gl_vertexid);
	glDeleteShader(gl_fragmentid);
	glDeleteProgram(gl_programid);
}

void shader::use_program() {
	glUseProgram(gl_programid);
	update_uniforms();
}

void shader::update_uniforms() {
	mpl::for_each_in_tuple(p_uniforms, [&](auto &uni_vector) {
		for (auto &uni : uni_vector) {
			updateValue(uni);
		}
	});
}

void shader::compile(GLuint gl_shaderid, const std::string &source) {
    const GLchar *source_cstr = source.c_str();
    const GLsizei source_size = source.size(); 

	glShaderSource(gl_shaderid, 1, &source_cstr, &source_size);
	glCompileShader(gl_shaderid);

	int length = 0;
	int max_length = 0;

	glGetShaderiv(gl_shaderid, GL_INFO_LOG_LENGTH, &max_length);

	std::string info_log(max_length, '\0');

	glGetShaderInfoLog(gl_shaderid, max_length, &length, info_log.data());

	GLint compiled = GL_FALSE;
	glGetShaderiv(gl_shaderid, GL_COMPILE_STATUS, &compiled);

	if (!compiled) {
		throw std::string("Failed to compile shader ") + name + "\n" + info_log;
	}
}