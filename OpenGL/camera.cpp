#include "camera.hpp"

bool Camera::viewChanged = true;
bool Camera::mouseClicked = false;

glm::vec2 Camera::deltaView = glm::vec2(0.f);

Camera::Camera(const glm::vec3& position, const glm::vec3& target, 
	float fieldOfView, float aspectRatio, float mouseSpeed) 
	:	position(position), 
		target(target), 
		FOV(fieldOfView), 
		aspectRatio(aspectRatio), 
		mouseSpeed(mouseSpeed),
		nearClipping(0.1f),
		up(glm::vec3(0.f, 1.f, 0.f)),
		angle(glm::vec2(3.14f, 0.f)) 
{ 
	viewMatrix = glm::lookAt(position, target, up);
	projMatrix = glm::infinitePerspective(FOV, aspectRatio, nearClipping);

	positions = vector<float>();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);

	float x = rand() % 200;//sin(glfwGetTime())  * 100.;
	float y = rand() % 200;//sin(glfwGetTime() * 0.6) * 16;
	float z = rand() % 200;//cos(glfwGetTime())  * 100.;

	positions.push_back(x);
	positions.push_back(y);
	positions.push_back(z);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 600, &positions[0], GL_STREAM_DRAW); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

//	glLineWidth(2.f);
}

void Camera::update(GLFWwindow *window)
{
	if (viewChanged && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
		recomputeView();

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += target * 2.5f;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= target * 2.5f;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= right * 2.5f;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += right * 2.5f;

	float x = positions.at(positions.size()-3) + (rand() % 32) - 16;
	float y = positions.at(positions.size()-2) + (rand() % 32) - 16;
	float z = positions.at(positions.size()-1) + (rand() % 32) - 16;

	x = glm::clamp(x, -100.f, 100.f);
	y = glm::clamp(y, 0.f, 100.f);
	z = glm::clamp(z, -100.f, 100.f);

	//if (mouseClicked) {
		positions.push_back(x);
		positions.push_back(y);
		positions.push_back(z);

		if (positions.size() > 600) {
			positions.erase(positions.begin(), positions.begin()+3);
		}

		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 600, &positions[0], GL_STREAM_DRAW); 
		mouseClicked = false;

	//}

	

	viewMatrix = glm::lookAt(position, position + target, up);
}

void Camera::draw() {
	glBindVertexArray(vao);
	glDrawArrays(GL_LINE_STRIP, 0, positions.size() / 3);
}

void Camera::recomputeView()
{
	angle += deltaView * mouseSpeed;

	angle.y = glm::clamp(angle.y, -1.f, 1.f);

	float m = angle.x - glm::half_pi<float>();
	float n = cos(angle.y);

	right = glm::vec3(sin(m), 0, cos(m));
	target = glm::vec3(n * sin(angle.x), sin(angle.y), n * cos(angle.x));
	up = glm::cross(right, target);

	viewChanged = false;
}

glm::mat4 Camera::getSkyboxViewMatrix() {
	return glm::lookAt(glm::vec3(0), target, up);
}
