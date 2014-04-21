#ifndef SKYBOX_H
#define SKYBOX_H

#include <glew.h>
#include <SOIL.h>
#include <Windows.h>

//#define FRONT	"negz.jpg"
//#define BACK	"posz.jpg"
//#define TOP		"posy.jpg"
//#define BOTTOM	"negy.jpg"
//#define LEFT	"negx.jpg"
//#define RIGHT	"posx.jpg"

#define FRONT	"i_ft.tga"
#define BACK	"i_bk.tga"
#define TOP		"i_up.tga"
#define BOTTOM	"i_dn.tga"
#define LEFT	"i_lf.tga"
#define RIGHT	"i_rt.tga"

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