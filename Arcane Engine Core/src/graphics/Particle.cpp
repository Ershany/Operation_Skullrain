#include "Particle.h"

namespace arcane { namespace graphics {

	Particle::Particle(opengl::VertexArray *vao, GLuint particleTexture, glm::vec3 &worldPos, int numParticles, bool isActive) 
		: m_VAO(vao), m_ParticleTexture(particleTexture), m_NumParticles(numParticles), m_WorldPos(worldPos) 
	{
		m_IsActive = isActive;

		if (m_IsActive) {
			m_Timer.reset();
		}
	}

	void Particle::setActive(bool choice) {
		m_IsActive = choice;
		if (m_IsActive) {
			m_Timer.reset();
		}
	}

	void Particle::update(float deltaTime) {
		
	}

	void Particle::draw(graphics::Shader &shader) {
		glActiveTexture(GL_TEXTURE0);
		shader.setUniform1i("particleTexture", 0);
		glBindTexture(GL_TEXTURE_2D, m_ParticleTexture);

		glm::mat4 model = glm::translate(glm::mat4(1.0f), m_WorldPos);
		shader.setUniformMat4("model", model);
		shader.setUniform1f("timer", m_Timer.elapsed());

		m_VAO->bind();
		glDrawArrays(GL_POINTS, 0, m_NumParticles);
		m_VAO->unbind();
	}

} }