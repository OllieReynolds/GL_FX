#version 420 core

in vec2 UV;
in float fog_fac;

uniform sampler2D tex;

out vec4 outColor;

const vec4 fog_colour = vec4 (0., 0., 1.0, 1.0);

vec4 glow(vec2 p, vec3 c, float pow) {
	return vec4(vec3(pow / (length(p)) * c), 1.0);
}

void main() {
	vec2 p = (gl_FragCoord.xy - 0.5 * vec2(640, 480)) / min(640, 480);
	vec4 c = glow(p, vec3(0.4, 0.4, 0.8), 0.02) * texture(tex, UV);

	//outColor = mix(texture(tex, UV), fog_colour, fog_fac);

	vec4 glowC = vec4(0.0);

	for (float i = 0; i < 1; i+=0.1) {
		glowC += glow((gl_FragCoord.xy - i * vec2(640, 480)) / min(640, 480), vec3(0.2+i, 0.8-i, 0.0), 0.05);
	}

	//vec4 fin = mix(texture(tex, UV), fog_colour, fog_fac);

	//outColor = smoothstep(0., 0.4, fin);

	outColor = mix(texture(tex, UV), fog_colour, fog_fac);
	//outColor = mix(texture(tex, UV), fog_colour, fog_fac) * glowC * vec4(step(1.0, mod(gl_FragCoord.x, 2.0)));
}

//
// OLD CODE
//
// Render normally with linear fog:
//outColor = mix(texture(tex, UV), fog_colour, fog_fac);
//
// Render with glowspots and scanlines
// outColor = mix(texture(tex, UV), fog_colour, fog_fac) * glowspot() * vec4(step(1.0, mod(gl_FragCoord.x, 2.0)));
