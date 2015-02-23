#version 420 core

in vec2 UV;
in float fog_fac;

uniform sampler2D tex;
uniform vec2 res;

out vec4 outColor;

const vec4 fog_colour = vec4 (0.f, 0.f, 0.f, 0.f);

vec4 glow(vec2 p, vec3 c, float pow) {
	return vec4(vec3(pow / (length(p)) * c), 1.0);
}

void main() {
    float dx = 8.0 * (1./res.x);
    float dy = 6.0 * (1./res.y);

    vec2 coord = vec2(dx * floor(UV.x / dx), dy * floor(UV.y / dy));

    vec4 c =  mix(texture(tex, coord), fog_colour, fog_fac);

    float gray = dot(c.rgb, vec3(0.299, 0.587, 0.114));

	outColor = vec4(gray);
}
