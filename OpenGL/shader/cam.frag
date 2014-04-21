#version 420 core
 
in vec4 exColor;

out vec4 outColor;

float rainbow(float x)
{
	x=fract(0.16666 * abs(x));
	if(x>.5) x = 1.0-x;
	if(x<.16666) return 0.0;
	if(x<.33333) return 6.0 * x-1.0;
	return 1.0;
}

void main()	
{
	vec2 position = ( 2.0*gl_FragCoord.xy - vec2(640, 480)) / 640;

	vec3 color = vec3(0.0);

	float r = length(position);
	float a = atan(position.y, position.x);

	float b = a*sin(.001)*24000.0/3.14159;
	outColor = vec4(rainbow(b+3.0), rainbow(b+1.0), rainbow(b+0.0), 1.0);

}