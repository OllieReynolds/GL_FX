#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include "shader.hpp"

class Drawable 
{
public:
	Drawable(float* vertices, float* uvs, float* normals,
		unsigned short* indices, GLenum usage);
	virtual ~Drawable();

	virtual void draw(Shader* shader) = 0;

protected:
	GLuint vao; 
	GLuint vbo[4];
	int elements;
};

#endif // DRAWABLE_HPP