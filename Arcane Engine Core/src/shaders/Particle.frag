#version 430 core

in vec2 uvs;
in vec3 FragColor;
in float Time;

out vec4 color;

uniform sampler2D particleTexture;

void main() {
	//color = texture(particleTexture, uvs);
	color = vec4(FragColor, 1 - (Time / 4.0));
}