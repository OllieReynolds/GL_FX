#pragma once

#include "drawable.hpp"
#include "camera.hpp"

#include "include\GLM-0.9.4.4\glm.hpp"

class meshv2 : public Drawable
{
public:
	meshv2();
	~meshv2();

	void draw(Shader* shader);

	static float vertices[36];
	static float uvs[36];
	static unsigned short indices[36];

	glm::mat4 modelMatrix;

	GLuint vao;
	GLuint vbo[4];
	int elements;
};

