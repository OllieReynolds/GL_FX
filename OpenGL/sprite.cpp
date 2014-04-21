#include "sprite.hpp"

Sprite::Sprite() {
	float points[] = {
		0.5, 0.5
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW); 
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
}

Sprite::~Sprite() {

}

void Sprite::draw() {
	glBindVertexArray(vao);
	glDrawArrays(GL_POINTS, 0, 1);
}