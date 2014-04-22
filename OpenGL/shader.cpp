#include "shader.hpp"

void Shader::create(string vsDir, string fsDir, const char* tcsDir, 
		const char* tesDir, const char* gsDir)
{
	shaders[VERT] = createShader(vsDir, GL_VERTEX_SHADER);
	shaders[FRAG] = createShader(fsDir, GL_FRAGMENT_SHADER);

	if (tcsDir) 
		shaders[TESC] = createShader(tcsDir, GL_TESS_CONTROL_SHADER);

	if (tesDir) 
		shaders[TESE] = createShader(tesDir, GL_TESS_EVALUATION_SHADER);

	if (gsDir)
		shaders[GEOM] = createShader(gsDir, GL_GEOMETRY_SHADER);

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
	}
}

GLuint Shader::createShader(string dir, GLenum type) {
	string s = loadFile(dir);
	const char* src = s.c_str();
	GLuint obj = glCreateShader(type);
	glShaderSource(obj, 1, &src, NULL);
	glCompileShader(obj);
	return obj;
}

void Shader::use() {
	glUseProgram(program);
}

//void Shader::updateMat4(glm::mat4 m, const GLchar* name) {
//	GLint loc = glGetUniformLocation(program, name);
//	glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
//}

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

string Shader::loadFile(const string& directory)
{
	ifstream ifs(directory);

	if (ifs.fail())
		MessageBox(NULL, L"Failed to load shader", NULL, NULL);

	string content(	(istreambuf_iterator<char>(ifs)	),
					(istreambuf_iterator<char>()	) );

	return content;
}