#include "shader.hpp"

int Shader::create(const shaderDir& dir)
{
	if (!dir.vertex && !dir.fragment)
		return -1;

	shaders[0] = createShader(dir.vertex, GL_VERTEX_SHADER);
	shaders[1] = createShader(dir.fragment, GL_FRAGMENT_SHADER);

	if (dir.tessControl) 
		shaders[2] = createShader(dir.tessControl, GL_TESS_CONTROL_SHADER);

	if (dir.tessEval) 
		shaders[3] = createShader(dir.tessEval, GL_TESS_EVALUATION_SHADER);

	if (dir.geometry)
		shaders[4] = createShader(dir.geometry, GL_GEOMETRY_SHADER);

	for (GLuint s : shaders)
		glAttachShader(program, s);
	
	glLinkProgram(program);
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);
 
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);
 
		glDeleteProgram(program);
		for (int i = 0; i < infoLog.size(); i++) {
			cout << infoLog.at(i);
		}

		return -1;
	}

	return 0;
}

GLuint Shader::createShader(const char* dir, GLenum type) {
	string s = loadFile(string(dir));
	const char* src = s.c_str();
	GLuint obj = glCreateShader(type);
	glShaderSource(obj, 1, &src, NULL);
	glCompileShader(obj);
	return obj;
}

void Shader::use() {
	glUseProgram(program);
}

void Shader::updateMat4(const GLchar* name, GLsizei n, const GLfloat* value) {
	GLint loc = glGetUniformLocation(program, name);
	glUniformMatrix4fv(loc, n, GL_FALSE, value);
}

void Shader::update1i(int i, const GLchar* name) {
	GLint loc = glGetUniformLocation(program, name);
	glUniform1i(loc, i);
}

void Shader::update1f(float d, const GLchar* name) {
	GLint loc = glGetUniformLocation(program, name);
	glUniform1f(loc, d);
}

void Shader::update2f(float x, float y, const GLchar* name) {
	GLint loc = glGetUniformLocation(program, name);
	glUniform2f(loc, x, y);

}

string Shader::loadFile(const string& directory) {
	ifstream ifs(directory);

	if (ifs.fail()) {
		cout << directory << endl;
		MessageBox(NULL, L"Failed to load shader", NULL, NULL);
	}

	string content(	(istreambuf_iterator<char>(ifs)	),
					(istreambuf_iterator<char>()	) );

	return content;
}