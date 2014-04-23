#include "meshv2.hpp"

float meshv2::vertices[36] = {
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f
};

float meshv2::uvs[36] = { 
		0.5f, 0.25f, 0.5f,
		0.1f, 0.8f, 0.7f,
		0.5f, 0.25f, 0.5f,
		0.1f, 0.8f, 0.7f,
		0.5f, 0.25f, 0.5f,
		0.1f, 0.8f, 0.7f,
		0.5f, 0.25f, 0.5f,
		0.1f, 0.8f, 0.7f
};

unsigned short meshv2::indices[36] = {
		0, 1, 2,
		2, 3, 1, 
		1, 5, 3,
		3, 7, 5,
		5, 4, 7, 
		7, 6, 4,
		4, 0, 2, 
		2, 6, 4,
		4, 0, 5,
		5, 1, 0,
		2, 3, 7,
		7, 6, 2
};

meshv2::meshv2()
	:	Drawable(vertices, uvs, NULL, indices, GL_STATIC_DRAW)
{ }

meshv2::~meshv2() {
}


void meshv2::draw(Shader* shader) {
	glm::mat4 MV = Camera::viewMatrix * modelMatrix;
	glm::mat4 MVP = Camera::projMatrix * MV;

	shader->update1f((float)glfwGetTime(), "time");
	shader->updateMat4("MVP", 1, glm::value_ptr(MVP));

	glBindVertexArray(vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[3]);
	glDrawElementsInstanced(GL_TRIANGLES, elements, GL_UNSIGNED_SHORT, 0, 1000000);
}