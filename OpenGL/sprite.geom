#version 440

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

uniform mat4 MVP;

void main() {
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();
 
	gl_Position.y = gl_in[0].gl_Position.y - 1.0;
	EmitVertex();

	gl_Position.y = gl_in[0].gl_Position.y;
	gl_Position.x = gl_in[0].gl_Position.x - 1.0;
	EmitVertex();

	gl_Position.y = gl_in[0].gl_Position.y - 1.0;
	gl_Position.x = gl_in[0].gl_Position.x - 1.0;
	EmitVertex();

	EndPrimitive();
}