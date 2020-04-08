#ifndef __SHADER_H__
#define __SHADER_H__

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <tuple>

#include "mpl.h"
class shader {
private:
	GLuint gl_shaderid = 0;
	
	const char *name;
	const GLenum type;

	GLint compiled = GL_FALSE;

public:
	shader(const char *name, const GLenum type, const std::string &source);

	~shader();

	bool compile_status() {
		return compiled;
	}

private:
	friend class shader_program;
};

template<typename T>
struct uniform {
	GLint location;
	const char *name;
	T *data;
};

using uniform_types = mpl::TypeList<int, float, glm::vec2, glm::vec3, glm::vec4, glm::mat4>;

class shader_program {
private:
	GLuint gl_programid = 0;

	std::vector<shader *> p_shaders;

	template<typename ... Ts>
	using uniform_list = std::tuple<std::vector<uniform<Ts>>...>;

	mpl::Rename<uniform_list, uniform_types> p_uniforms;

public:
	template <typename ... Ts>
	shader_program(Ts &... shaders) : p_shaders {&shaders ...} {
		gl_programid = glCreateProgram();

		for (shader *i : p_shaders) {
			glAttachShader(gl_programid, i->gl_shaderid);
		}

		glLinkProgram(gl_programid);
	}

	~shader_program() {
		if (gl_programid) {
			for (shader *i : p_shaders) {
				glDetachShader(gl_programid, i->gl_shaderid);
			}
			glDeleteProgram(gl_programid);
		}
	}

	template<typename T>
	void add_uniform(const char *name, T *data) {
		int location = glGetUniformLocation(gl_programid, name);
		std::get<mpl::IndexOf<uniform<T>, uniform_types>>(p_uniforms).emplace_back(location, name, data);
	}

	void use_program() {
		glUseProgram(gl_programid);
		update_uniforms();
	}

	void update_uniforms();
};

#endif