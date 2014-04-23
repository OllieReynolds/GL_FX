#include "scene.hpp"

bool Scene::recompileShaders = false;

Scene::Scene() 
	:	activeShader(NULL)
{
	camera = new Camera(
		glm::vec3(0.0, 0.0, 0.0),	// Position
		glm::vec3(0.0, 0.0, -4.0),	// Target
		90.f,	// FOV
		1.3333f, // Aspect ratio
		0.002f	// mouse speed
	);
	camera->initMatrices();
	
	shaderMgr = new ShaderManager();

	plane = new Plane(10000.f, 10000.f, 100, 100);

	skybox = new Skybox();

	panel = new Panel();

	test = new meshv2();
}

Scene::~Scene() {
	delete panel;
	delete skybox;
	delete plane;
	delete camera;

	delete shaderMgr;
}

void Scene::draw(GLFWwindow *window)
{
	if (recompileShaders) {
		// Implement shader program recompilation here
		// Refactor to function when working
		recompileShaders = false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, panel->fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	camera->update(window);

	activeShader = shaderMgr->getShader("Cubefield"); 
	test->draw(activeShader);
	
	activeShader = shaderMgr->getShader("Plane");
	plane->draw(activeShader);

	activeShader = shaderMgr->getShader("Camera");
	camera->draw(activeShader);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);

	activeShader = shaderMgr->getShader("Panel");
	panel->draw(activeShader);
}