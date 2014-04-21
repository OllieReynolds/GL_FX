#version 420 core
 
in vec4 exColor;
in float fog_fac;

out vec4 outColor;

const vec4 fog_colour = vec4 (1.0, 1.0, 1.0, 1.0);

void main()	
{
	outColor = mix(exColor, fog_colour, fog_fac);

	//vec4 fin = mix(exColor, fog_colour, fog_fac);

	//outColor = smoothstep(0., 0.8, fin);
}