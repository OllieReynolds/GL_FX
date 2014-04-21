#version 420 core

layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec2 st;

uniform mat4 M;

out vec2 UV;

void main() {
	gl_Position = M * vec4(inPosition, 0.0, 1.0);
	UV = st;
}