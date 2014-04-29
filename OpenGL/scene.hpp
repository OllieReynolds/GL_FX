#ifndef SCENE_HPP
#define SCENE_HPP

#include "camera.hpp"
#include "shader.hpp"
#include "skybox.h"
#include "panel.hpp"
#include "plane.hpp"
#include "audioplayer.hpp"
#include "meshv2.hpp"
#include "shader_manager.hpp"

class Scene
{
public:
	Scene();
	~Scene();

	void create();
	void draw(GLFWwindow *window);
	void kill();

	static bool recompileShaders;

private:
	Camera*	camera;

	meshv2* test;

	//Mesh*	mesh;
	Plane*	plane;

	Skybox* skybox;

	Panel*	panel;

	Shader* activeShader;

	ShaderManager* shaderMgr;
	
};

#endif // SCENE_HPP