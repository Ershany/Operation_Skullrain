#version 430 core

layout (points) in;
layout (triangle_strip, max_vertices = 4) out;

in vec3 Color[];
in float time[];

out vec2 uvs;
out vec3 FragColor;
out float Time;

uniform mat4 projection;

float particleSize = 0.3f;

void main() {
	vec4 position = gl_in[0].gl_Position;

	// Vertex 1
	gl_Position = projection * vec4(position.x - particleSize, position.y - particleSize, position.z, 1.0);
	uvs = vec2(0.0, 1.0);
	FragColor = Color[0];
	Time = time[0];
	EmitVertex();

	// Vertex 2
	gl_Position = projection * vec4(position.x + particleSize, position.y - particleSize, position.z, 1.0);
	uvs = vec2(1.0, 1.0);
	FragColor = Color[0];
	Time = time[0];
	EmitVertex();

	// Vertex 3
	gl_Position = projection * vec4(position.x - particleSize, position.y + particleSize, position.z, 1.0);
	uvs = vec2(0.0, 0.0);
	FragColor = Color[0];
	Time = time[0];
	EmitVertex();

	// Vertex 4
	gl_Position = projection * vec4(position.x + particleSize, position.y + particleSize, position.z, 1.0);
	uvs = vec2(1.0, 0.0);
	FragColor = Color[0];
	Time = time[0];
	EmitVertex();
	EndPrimitive();
}