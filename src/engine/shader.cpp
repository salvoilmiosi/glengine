#include "shader.h"

#include <iostream>

#include <glm/gtc/type_ptr.hpp>

shader::shader(const char *name, const GLenum type, const std::string &source) : type(type) {
	gl_shaderid = glCreateShader(type);

    const GLchar *source_cstr = source.c_str();
    const GLsizei source_size = source.size(); 

	glShaderSource(gl_shaderid, 1, &source_cstr, &source_size);
	glCompileShader(gl_shaderid);

	int length = 0;
	int max_length = 0;

	glGetShaderiv(gl_shaderid, GL_INFO_LOG_LENGTH, &max_length);

	char *info_log = (char *) malloc(max_length);

	glGetShaderInfoLog(gl_shaderid, max_length, &length, info_log);
	if (length > 0) {
		std::cout << "Compile error in shader " << name << ":" << std::endl << info_log << std::endl;
	}

	free(info_log);

	glGetShaderiv(gl_shaderid, GL_COMPILE_STATUS, &compiled);
}

shader::~shader() {
    glDeleteShader(gl_shaderid);
}

void updateValue(const uniform<int> &uni) {
	glUniform1i(uni.location, *uni.data);
}
void updateValue(const uniform<float> &uni) {
	glUniform1f(uni.location, *uni.data);
}
void updateValue(const uniform<glm::vec2> &uni) {
	glUniform2fv(uni.location, 1, glm::value_ptr(*uni.data));
}
void updateValue(const uniform<glm::vec3> &uni) {
	glUniform3fv(uni.location, 1, glm::value_ptr(*uni.data));
}
void updateValue(const uniform<glm::vec4> &uni) {
	glUniform4fv(uni.location, 1, glm::value_ptr(*uni.data));
}
void updateValue(const uniform<glm::mat4> &uni) {
	glUniformMatrix4fv(uni.location, 1, false, glm::value_ptr(*uni.data));
}

void shader_program::update_uniforms() {
	mpl::for_each_in_tuple(p_uniforms, [&](auto &uni_vector) {
		for (auto &uni : uni_vector) {
			updateValue(uni);
		}
	});
}
