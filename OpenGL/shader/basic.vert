#version 420 core
 
layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec4 inColor;	

out vec4 exColor;					
						
uniform mat4 MVP;
uniform float time;

const float INSTANCE_COUNT = 1337.f;

vec4 instanceToVec(int id) {
	int a = int(pow(INSTANCE_COUNT, .3));
	int b = int(INSTANCE_COUNT / a);

	return vec4(id % a, floor((id / a) % a), floor((id / b) % a), 1.);
}

void main() {
	vec4 v = instanceToVec(gl_InstanceID);
	gl_Position = MVP * (inPosition + (v * 10));

	exColor = inColor;
}