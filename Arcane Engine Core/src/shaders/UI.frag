#version 430 core

in vec2 TexCoords;

out vec4 color;

uniform sampler2D uiTexture;

void main() {
	color = texture(uiTexture, TexCoords);
}