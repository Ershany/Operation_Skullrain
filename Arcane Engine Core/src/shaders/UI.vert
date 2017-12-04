#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out vec2 TexCoords;

uniform mat4 model;

void main() {
	gl_Position = model * vec4(position, 1.0);
	TexCoords = texCoords;

	gl_Position.z = -1.0;
}