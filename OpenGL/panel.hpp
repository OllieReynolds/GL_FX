#ifndef PANEL_HPP
#define PANEL_HPP

#include <iostream>

#include "include\GLEW_64-1.10.0\glew.h"
#include "include\SOIL\SOIL.h"
#include "include\GLM-0.9.4.4\glm.hpp"
#include "include\GLM-0.9.4.4\gtc\quaternion.hpp"
#include "include\GLM-0.9.4.4\gtx\quaternion.hpp"
#include "include\GLM-0.9.4.4\gtc\matrix_transform.hpp"

#include "constants.hpp"
#include "shader.hpp"

class Panel {
public:
	Panel();
	~Panel();

	void draw(Shader* shader);

	GLuint fbo;
	glm::mat4 modelMatrix;

private:
	GLuint vao, vbo, vbo2;
	GLuint rbo;
	GLuint texture_data;	
};

#endif // PANEL_HPP