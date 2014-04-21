#version 420 core

layout (location = 0) in vec3 inPosition;

out vec3 texcoords;

uniform mat4 P, V;

void main() {
	gl_Position = P * V * vec4(inPosition, 1.0);

	texcoords = inPosition;
}