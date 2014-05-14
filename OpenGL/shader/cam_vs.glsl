#version 420 core

layout (location = 0) in vec3 inPosition;

uniform mat4 MVP;

out vec4 exColor;

void main() {
	gl_Position = MVP * vec4(inPosition, 1.0);
	exColor = vec4(inPosition, 1.0);
}