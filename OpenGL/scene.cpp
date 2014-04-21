#include "scene.hpp"

bool Scene::recompileShaders = false;

Scene::Scene() {
	camera = new Camera(
		glm::vec3(0.0, 0.0, 0.0),	// Position
		glm::vec3(0.0, 0.0, -4.0),	// Target
		90.f,	// FOV
		1.3333f, // Aspect ratio
		0.002f	// mouse speed
	);
	
	basicShader = new Shader();
	basicShader->create("basic.vert", "basic.frag", NULL, NULL, NULL);
	
	skyboxShader = new Shader();
	skyboxShader->create("skybox.vert", "skybox.frag", NULL, NULL, NULL);

	panelShader = new Shader();
	panelShader->create("panel.vert", "panel.frag", NULL, NULL, NULL);

	planeShader = new Shader();
	planeShader->create("plane.vert", "panel.frag", NULL, NULL, NULL);

	camShader = new Shader();
	camShader->create("cam.vert", "cam.frag", NULL, NULL, NULL);

	mesh = new Mesh();
	mesh->create();

	plane = new Plane(10000.f, 10000.f, 100, 100);
	plane->modelMatrix *= glm::translate(glm::mat4(1.0), glm::vec3(0, -64, 0));

	skybox = new Skybox();
	glClearColor(1.f, 1.f, 1.f, 1.f);

	panel = new Panel();
}

Scene::~Scene() {
	delete panel;
	delete skybox;

	delete plane;

	delete camera;
	mesh->kill();
	

	//basicShader->kill();
	//skyboxShader->kill();
}

void Scene::draw(GLFWwindow *window)
{
	if (recompileShaders) {
		basicShader = new Shader();
		basicShader->create("basic.vert", "basic.frag", NULL, NULL, NULL);
	
		skyboxShader = new Shader();
		skyboxShader->create("skybox.vert", "skybox.frag", NULL, NULL, NULL);

		panelShader = new Shader();
		panelShader->create("panel.vert", "panel.frag", NULL, NULL, NULL);

		planeShader = new Shader();
		planeShader->create("plane.vert", "panel.frag", NULL, NULL, NULL);
		recompileShaders = false;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, panel->fbo);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	camera->update(window);

	skyboxShader->use();
	skyboxShader->updateMat4(camera->projMatrix, "P");
	skyboxShader->updateMat4(camera->getSkyboxViewMatrix(), "V");
	skybox->draw();

	glm::mat4 MV = camera->viewMatrix * mesh->modelMatrix * AudioPlayer::scaleMatrix;
	glm::mat4 MVP = camera->projMatrix * MV;
	basicShader->use();
	basicShader->update1f((float)glfwGetTime(), "time");
	basicShader->updateMat4(MV, "MV");
	basicShader->updateMat4(MVP, "MVP");
	mesh->drawInstanced(1000);

	MV = camera->viewMatrix * plane->modelMatrix;
	MVP = camera->projMatrix * MV;
	planeShader->use();
	planeShader->update1i(2, "tex");
	planeShader->updateMat4(MV, "MV");
	planeShader->updateMat4(MVP, "MVP");
	plane->draw();

	MV = camera->viewMatrix * camera->modelMatrix;
	MVP = camera->projMatrix * MV;
	camShader->use();
	camShader->updateMat4(MV, "MV");
	camShader->updateMat4(MVP, "MVP");
	camera->draw();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST);

	panelShader->use();
	panelShader->updateMat4(panel->modelMatrix, "M");
	panel->draw();
}