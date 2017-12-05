#pragma once

//Dependancies
#include "../Dependancies.h"

//Operation Skullrain Headers
#include "../platform/OpenGL/VertexArray.h"
#include "Shader.h"
#include "../utils/Timer.h"

namespace arcane { namespace graphics {

	class Particle {
	public:
		Particle(opengl::VertexArray *vao, GLuint particleTexture, glm::vec3 &worldPos, int numParticles, bool isActive = true);

		void update(float deltaTime);
		void draw(graphics::Shader &shader);

		// Setters
		inline void setPosition(glm::vec3 &pos) { m_WorldPos = pos; }
		void setActive(bool choice);

		// Getters
		inline bool isActive() { return m_IsActive; }
	private:
		opengl::VertexArray *m_VAO;
		glm::vec3 m_WorldPos;
		int m_NumParticles;
		GLuint m_ParticleTexture;

		Timer m_Timer;
		bool m_IsActive;
	};

} }