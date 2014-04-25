#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "include\GLEW_64-1.10.0\glew.h"
#include "include\GLFW_64-3.0.1\glfw3.h"
#include "include\GLM-0.9.4.4\glm.hpp"
#include "include\GLM-0.9.4.4\gtc\quaternion.hpp"
#include "include\GLM-0.9.4.4\gtc\matrix_transform.hpp"
#include "include\GLM-0.9.4.4\gtx\quaternion.hpp"

class Mesh
{
public:
	enum Buffer { VERTEX, UV, INDEX, NORMAL };

	void create();
	void kill();

	void draw();
	void drawInstanced(int count);

public:
	glm::mat4 modelMatrix;
	glm::mat4 rotMatrix;

	std::vector<glm::mat4> translationMatrices;

private:
	int	elementCount;

	GLuint buffer[4];
	GLuint vertexArrayObject;

	
};

#endif // MESH_HPP