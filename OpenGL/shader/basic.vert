#version 420 core
 
layout (location = 0) in vec4 inPosition;
layout (location = 1) in vec4 inColor;	

out vec4 exColor;		
out float fog_fac;				

uniform mat4 MV;						
uniform mat4 MVP;

uniform float time;

const float min_fog_radius = 1.0;
const float max_fog_radius = 1000.0;

vec4 calcNewPosition(vec4 inputPos)
{
	int amplitude	= 32;
	int frequency	= 2;
	int distance	= 4;

	float val = frequency * gl_InstanceID + time;

	inputPos.x += amplitude * sin(val);
	inputPos.y += amplitude * cos(val);
	inputPos.z -= gl_InstanceID * distance;

	return inputPos;
}

void main()
{
	vec4 finalPos = calcNewPosition(inPosition);
	vec3 finalPosCamSpace = (MV * finalPos).xyz;

	float dist = length(-finalPosCamSpace);
	float fog_f = (dist - min_fog_radius) / (max_fog_radius - min_fog_radius);
	fog_fac = clamp(fog_f, 0.0, 1.0);

	gl_Position = MVP * finalPos;
	exColor = inColor;
}