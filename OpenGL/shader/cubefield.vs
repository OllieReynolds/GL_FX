#version 420 core
 
layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec4 inColor;	

out vec4 exColor;					
						
uniform mat4 MVP;
uniform float time;

const float OFFSET = 5.f;
const float INSTANCE_COUNT = 1000000.f;

float rand(vec2 co){
	return fract(sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453);
}

vec3 instanceToVec(int id) {
	int a = int(pow(INSTANCE_COUNT, .3));
	int b = int(INSTANCE_COUNT / a);

	float x = (id % a) * OFFSET;
	float y = ((id / a) % a) * OFFSET;
	float z = ((id / b) % a) * OFFSET;

	return vec3(x, y, z); 
}

void main() {
	vec4 v = vec4(instanceToVec(gl_InstanceID), 1.0);
	gl_Position = MVP * (inPosition + v);

	exColor = inColor;
}