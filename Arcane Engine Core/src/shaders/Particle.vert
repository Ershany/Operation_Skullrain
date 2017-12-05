#version 430 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

out vec3 Color;
out float time;

uniform mat4 model;
uniform mat4 view;
uniform float timer;

float speed = 200.0f;
float gravity = 1.0f;

void main() {
	float t = timer - 4.0 * floor(timer / 4.0);

	vec3 pos = position + (normal * t * speed) - (gravity * speed * vec3(0.0, 1.0, 0.0) * t * t);
	gl_Position = view * model * vec4(pos, 1.0);
	Color = color;
	time = t;
}