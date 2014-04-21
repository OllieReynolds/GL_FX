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
	void update();
	void kill();

	void draw();
	void drawInstanced(int count);

private:
	void loadModel();

public:
	glm::mat4 modelMatrix;
	glm::mat4 rotMatrix;

private:
	int	elementCount;

	GLuint buffer[3];
	GLuint vertexArrayObject;
};

#endif // MESH_HPP