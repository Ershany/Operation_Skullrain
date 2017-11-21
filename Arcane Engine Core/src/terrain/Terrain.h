#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "..\graphics\Mesh.h"
#include "..\graphics\Shader.h"
#include <SOIL.h>
#include <stb_image_aug.h>

namespace arcane { namespace terrain {

	class Terrain {
	private:
		GLfloat m_TerrainSize;
		GLuint m_VertexSideCount;
		GLushort m_HeightMapScale;
		unsigned char *heightMapImage;

		glm::mat4 m_ModelMatrix;
		glm::vec3 m_Position;
		graphics::Mesh *m_Mesh;
	public:
		Terrain(glm::vec3 &worldPosition);
		~Terrain();

		void Draw(graphics::Shader &shader) const;

		GLfloat getVertexHeight(int x, int y);

		inline const glm::vec3& getPosition() const { return m_Position; }
		inline const GLuint getVertexSideCount() const { return m_VertexSideCount; }
		inline const GLuint getTerrainScale() const { return m_TerrainSize; }
	private:
		glm::vec3 calculateNormal(int x, int z);
	};

} }

