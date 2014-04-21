#ifndef PLANE_HPP
#define PLANE_HPP

#include <glew.h>
#include <glm.hpp>
#include <SOIL.h>

class Plane {
public:
	Plane(float sizeX, float sizeZ, int facesX, int facesZ);
	~Plane();

	void draw();

	glm::mat4 modelMatrix;
	GLuint texture_data;

private:
	int faces;
	GLuint vao;
	GLuint buffer[4];
	
};

#endif // PLANE_HPP