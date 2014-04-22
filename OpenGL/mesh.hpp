#ifndef MESH_HPP
#define MESH_HPP

//#define TEXTURES_ENABLED

#include <vector>

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/matrix_transform.hpp> 

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