#version 420 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec2 st;

uniform mat4 MVP;
uniform mat4 MV;

out vec2 UV;
out float fog_fac;

const float min_fog_radius = 1.0;
const float max_fog_radius = 1000.0;

void main() {
	gl_Position = MVP * vec4(inPosition, 1.0);
	vec3 finalPosCamSpace = (MV * vec4(inPosition, 1.0)).xyz;

	float dist = length(-finalPosCamSpace);
	float fog_f = (dist - min_fog_radius) / (max_fog_radius - min_fog_radius);
	fog_fac = clamp(fog_f, 0.0, 1.0);


	UV = st;
}