#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <gtc/quaternion.hpp>
#include <gtx/quaternion.hpp>
#include <gtc/matrix_transform.hpp> 
#include <vector>

using std::vector;

class Camera
{
public:
	Camera(const glm::vec3& position, const glm::vec3& target, 
		float fieldOfView, float aspectRatio, float mouseSpeed);

	void update(GLFWwindow *window);

	void draw();

	static bool viewChanged;
	static bool mouseClicked;

	static glm::vec2 deltaPos;
	static glm::vec2 deltaView;

	glm::mat4 viewMatrix;
	glm::mat4 projMatrix;
	glm::mat4 modelMatrix;

	glm::mat4 getSkyboxViewMatrix();

private:
	static const float moveSpeed;


	void recomputeView();

	glm::fquat lerp(const glm::fquat& v0, const glm::fquat& v1, float angle);
	glm::fquat slerp(const glm::fquat& v0, const glm::fquat& v1, float angle);

	float FOV;
	float aspectRatio;
	float nearClipping;

	float mouseSpeed;

	glm::vec2 angle;

	glm::vec3 up;
	glm::vec3 target;
	glm::vec3 position;

	glm::vec3 right;

	vector<float> positions;


	GLuint vao, vbo;
};

#endif // CAMERA_HPP