#ifndef SHADER_HPP
#define SHADER_HPP

#include <glew.h>
#include <glfw3.h>
#include <gtc/matrix_transform.hpp> 
#include <gtc/type_ptr.hpp>
#include <vector>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

enum ShaderTypes 
{ 
	VERT,
	FRAG,
	TESC,
	TESE,
	GEOM,
};

class Shader
{
public:
	Shader()
		:	program(glCreateProgram()) { }

	~Shader() {
		glUseProgram(NULL);

		for (GLuint s : shaders) {
			glDetachShader(program, s);
			glDeleteShader(s);
		}

		glDeleteProgram(program);
	}

	void create(string vsDir, string fsDir, const char* tcsDir, 
		const char* tesDir, const char* gsDir);

	void use();

	void updateMat4(glm::mat4 m, const GLchar* name);
	void update1i(int i, const GLchar* name);
	void update1f(float d, const GLchar* name);

private:
	GLuint createShader(string dir, GLenum type);
	string loadFile(const string& directory);

	GLuint program; 
	GLuint shaders[5];
};

#endif // SHADER_HPP