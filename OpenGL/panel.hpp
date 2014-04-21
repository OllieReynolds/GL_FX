#ifndef PANEL_HPP
#define PANEL_HPP

#include <glew.h>
#include <SOIL.h>
#include <iostream>
#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/matrix_transform.hpp> 

class Panel {
public:
	Panel();
	~Panel();

	void draw();

	GLuint fbo;
	glm::mat4 modelMatrix;

private:
	GLuint vao, vbo, vbo2;
	GLuint rbo;
	GLuint texture_data;	
};

#endif // PANEL_HPP