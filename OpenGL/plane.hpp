#ifndef PLANE_HPP
#define PLANE_HPP

#include "include\GLEW_64-1.10.0\glew.h"
#include "include\GLM-0.9.4.4\glm.hpp"
#include "include\SOIL\SOIL.h"

#include "camera.hpp"
#include "constants.hpp"
#include "shader.hpp"

class Plane {
public:
	Plane(float sizeX, float sizeZ, int facesX, int facesZ);
	~Plane();

	void draw(Shader* shader);

	glm::mat4 modelMatrix;
	GLuint texture_data;

private:
	int faces;
	GLuint vao;
	GLuint buffer[4];
	
};

#endif // PLANE_HPP