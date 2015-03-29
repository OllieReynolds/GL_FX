#include "scene.hpp"

#include "constants.hpp"

static GLFWwindow* window;

static void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

static glm::vec2 size;
static glm::vec2 center;

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_DEPTH_BITS, 24);
	glfwWindowHint(GLFW_SAMPLES, SAMPLES);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_VERSION_MAJOR, VER_MAJOR);
	glfwWindowHint(GLFW_VERSION_MINOR, VER_MINOR);

	window = glfwCreateWindow(WIDTH, HEIGHT, "Demo", NULL, NULL);

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	int x, y;
	glfwGetWindowSize(window, &x, &y);

	size	= glm::vec2(x, y);
	center	= glm::vec2(size * 0.5f);
	glfwSetCursorPos(window, center.x, center.y);

	glewInit();

	glEnable(GL_DEPTH_TEST);

	Scene* scene = new Scene();

	while (!glfwWindowShouldClose(window)) {
		scene->draw(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete scene;

	glfwTerminate();
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_F5 && action == GLFW_PRESS) {
		Scene::recompileShaders = true;
	}
		
} 

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{
	glfwSetCursorPos(window, center.x, center.y);

	Camera::viewChanged = true;
	Camera::deltaView	= glm::vec2(center.x - xPos, center.y - yPos);
}