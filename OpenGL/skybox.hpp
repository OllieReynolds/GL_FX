#ifndef SKYBOX_H
#define SKYBOX_H

#include "include\GLEW_64-1.10.0\glew.h"
#include "include\SOIL\SOIL.h"

#include <Windows.h>

#define FRONT	"textures/i_ft.tga"
#define BACK	"textures/i_bk.tga"
#define TOP		"textures/i_up.tga"
#define BOTTOM	"textures/i_dn.tga"
#define LEFT	"textures/i_lf.tga"
#define RIGHT	"textures/i_rt.tga"

class Skybox
{
public:
	Skybox();
	~Skybox();

	void draw();

private:
	GLuint vbo;
	GLuint vao;
	GLuint skybox_texture;

};

#endif // SKYBOX_H