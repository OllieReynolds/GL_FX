#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <glew.h>
#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/matrix_transform.hpp> 

class Sprite {
public:
	Sprite();
	~Sprite();

	void draw();

	glm::mat4 model;

private:
	GLuint vao, vbo;

	
};

#endif // SPRITE_HPP