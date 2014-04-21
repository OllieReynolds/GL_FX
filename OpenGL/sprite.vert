#version 440

layout (location = 0) in vec2 inPos;

uniform mat4 MV;

void main() {
	gl_Position =  MV * vec4(inPos, 0.0, 1.0);
}