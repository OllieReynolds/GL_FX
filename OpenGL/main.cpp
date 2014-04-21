#include "scene.hpp"

#include "audioplayer.hpp"

static GLFWwindow* window;

static void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void onClick(GLFWwindow* window, int button, int action, int mods);

static glm::vec2 size;
static glm::vec2 center;

static const int SAMPLES	=   2;
static const int MAJOR		=   4;
static const int MINOR		=	4;
static const int WIDTH		= 640;
static const int HEIGHT		= 480;


int main()
{
	glfwInit();
	glfwWindowHint( GLFW_SAMPLES, SAMPLES );
	glfwWindowHint( GLFW_RESIZABLE, GL_FALSE );
	glfwWindowHint( GLFW_VERSION_MAJOR, MAJOR );
	glfwWindowHint( GLFW_VERSION_MINOR, MINOR );

	window = glfwCreateWindow(WIDTH, HEIGHT, "Demo", NULL, NULL);

	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	glfwSetMouseButtonCallback(window, onClick);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	int x, y;
	glfwGetWindowSize(window, &x, &y);

	size	= glm::vec2(x, y);
	center	= glm::vec2(size * 0.5f);
	glfwSetCursorPos(window, center.x, center.y);

	glewInit();

	glDepthFunc(GL_LESS);

	Scene* scene = new Scene();

	AudioPlayer* player = new AudioPlayer();
	player->loadTrack("http://88.80.10.21:8086/bitjam.mp3");

	while (!glfwWindowShouldClose(window)) {
		player->updatePlayback();
		scene->draw(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	delete player;
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

void onClick(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		Camera::mouseClicked = true;
	}
}