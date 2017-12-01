#version 430 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 3) out;

uniform mat4 view;
uniform mat4 projection;

uniform float timer;

in vec3 Normal[];
in vec3 FragPos[];
in vec2 TexCoords[];

out vec3 aNormal;
out vec3 aFragPos;
out vec2 aTexCoords;

vec3 CalculateTriangleNormal();

void main() {
	vec3 triangleNormal = CalculateTriangleNormal();

	gl_Position = projection * view * (gl_in[0].gl_Position + vec4((timer * 100.0f) * (triangleNormal + vec3(0.0, -0.5, 0.0) * timer), 0.0));
	aNormal = Normal[0];
	aFragPos = FragPos[0];
	aTexCoords = TexCoords[0];
	EmitVertex();

	gl_Position = projection * view * (gl_in[1].gl_Position + vec4((timer * 100.0f) * (triangleNormal + vec3(0.0, -0.5, 0.0) * timer), 0.0));
	aNormal = Normal[1];
	aFragPos = FragPos[1];
	aTexCoords = TexCoords[1];
	EmitVertex();

	gl_Position = projection * view * (gl_in[2].gl_Position + vec4((timer * 100.0f) * (triangleNormal + vec3(0.0, -0.5, 0.0) * timer), 0.0));
	aNormal = Normal[2];
	aFragPos = FragPos[2];
	aTexCoords = TexCoords[2];
	EmitVertex();
    EndPrimitive();
}

vec3 CalculateTriangleNormal() {
	vec3 side1 = vec3(gl_in[0].gl_Position - gl_in[1].gl_Position);
	vec3 side2 = vec3(gl_in[2].gl_Position - gl_in[1].gl_Position);
	return normalize(cross(side1, side2));
}