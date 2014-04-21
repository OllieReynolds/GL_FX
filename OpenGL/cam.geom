#version 420

layout (points) in;
layout (line_strip, max_vertices = 4) out;

uniform mat4 MVP;

void main() {
	gl_Position = gl_in[0].gl_Position;
	EmitVertex();
 
	gl_Position.y = gl_in[0].gl_Position.y + 10.0;
	EmitVertex();

	gl_Position.y = gl_in[0].gl_Position.y + 10.0;
	gl_Position.x = gl_in[0].gl_Position.x + 10.0;
	EmitVertex();

	gl_Position.y = gl_in[0].gl_Position.y + 10.0;
	EmitVertex();

	EndPrimitive();
}