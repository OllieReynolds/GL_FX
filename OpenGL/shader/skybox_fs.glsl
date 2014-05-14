#version 420 core

in vec3 texcoords;
uniform samplerCube skybox_texture;
out vec4 outColor;

void main() {
	outColor = texture(skybox_texture, texcoords);
}