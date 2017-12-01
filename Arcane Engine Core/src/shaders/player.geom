#version 430 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 Normal[];
in vec3 FragPos[];
in vec2 TexCoords[];

out vec3 aNormal;
out vec3 aFragPos;
out vec2 aTexCoords;

void main() {
	gl_Position = gl_in[0].gl_Position;
	aNormal = Normal[0];
	aFragPos = FragPos[0];
	aTexCoords = TexCoords[0];
	EmitVertex();

	gl_Position = gl_in[1].gl_Position;
	aNormal = Normal[1];
	aFragPos = FragPos[1];
	aTexCoords = TexCoords[1];
	EmitVertex();

	gl_Position = gl_in[2].gl_Position;
	aNormal = Normal[2];
	aFragPos = FragPos[2];
	aTexCoords = TexCoords[2];
	EmitVertex();
    EndPrimitive();
}