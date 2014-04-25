#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "include\GLEW_64-1.10.0\glew.h"
#include "include\GLFW_64-3.0.1\glfw3.h"
#include "include\GLM-0.9.4.4\glm.hpp"
#include "include\GLM-0.9.4.4\gtc\quaternion.hpp"
#include "include\GLM-0.9.4.4\gtx\quaternion.hpp"
#include "include\GLM-0.9.4.4\gtc\matrix_transform.hpp"


#include <vector>

#include "shader.hpp"

class Camera
{
public:
	Camera(const glm::vec3& position, const glm::vec3& target, 
		float fieldOfView, float aspectRatio, float mouseSpeed);

	void update(GLFWwindow *window);

	void draw(Shader* shader);

	static bool viewChanged;
	static bool mouseClicked;

	static glm::vec2 deltaPos;
	static glm::vec2 deltaView;

	static glm::mat4 viewMatrix;
	static glm::mat4 projMatrix;
	glm::mat4 modelMatrix;

	glm::mat4 getSkyboxViewMatrix();
	void initMatrices();

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

	std::vector<float> positions;


	GLuint vao, vbo;
};

#endif // CAMERA_HPP