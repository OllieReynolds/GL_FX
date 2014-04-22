#include "mesh.hpp"

void Mesh::create()
{
	float vertices[36] =
	{
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f
	};

	float colors[36]=
	{
		0.5f, 0.25f, 0.5f,
		0.1f, 0.8f, 0.7f,
		0.5f, 0.25f, 0.5f,
		0.1f, 0.8f, 0.7f,
		0.5f, 0.25f, 0.5f,
		0.1f, 0.8f, 0.7f,
		0.5f, 0.25f, 0.5f,
		0.1f, 0.8f, 0.7f,
	};

	unsigned short indices[36]=
	{
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

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);

	glGenBuffers(4, buffer);

	glBindBuffer(GL_ARRAY_BUFFER, buffer[VERTEX]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
	glVertexAttribPointer(VERTEX, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(VERTEX);
 
	glBindBuffer(GL_ARRAY_BUFFER, buffer[UV]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
	glVertexAttribPointer(UV, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(UV);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDEX]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &elementCount);

	modelMatrix *= glm::scale(glm::mat4(1.), glm::vec3(10.f, 10.f, 10.f));
}

void Mesh::kill()
{
	glDisableVertexAttribArray(UV);
	glDisableVertexAttribArray(VERTEX);
	 
	glBindBuffer(GL_ARRAY_BUFFER, 0);
 
	glDeleteBuffers(3, buffer);
 
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &vertexArrayObject);
}


void Mesh::drawInstanced(int count)
{
	glBindVertexArray(vertexArrayObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[INDEX]);
	glDrawElementsInstanced(GL_TRIANGLES, elementCount, GL_UNSIGNED_SHORT, 0, count);
}