#include "ParticleRenderer.h"

namespace arcane { namespace graphics{

	ParticleRenderer::ParticleRenderer(graphics::Window *window, Camera *camera, game::Player *player) : m_Window(window), m_Camera(camera) {
	}

	void ParticleRenderer::addParticle(Particle *p) {
		m_ParticleQueue.push_back(p);
	}

	void ParticleRenderer::update(float deltaTime) {
		auto iter = m_ParticleQueue.begin();
		while (iter != m_ParticleQueue.end()) {
			if ((*iter)->isActive()) {
				(*iter)->update(deltaTime);
			}

			iter++;
		}
	}

	void ParticleRenderer::render(graphics::Shader &shader) {
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);

		auto iter = m_ParticleQueue.begin();
		while (iter != m_ParticleQueue.end()) {
			if ((*iter)->isActive()) {
				shader.setUniformMat4("view", m_Camera->getViewMatrix());
				shader.setUniformMat4("projection", glm::perspective(glm::radians(m_Camera->getFOV()), (float)m_Window->getWidth() / (float)m_Window->getHeight(), 0.1f, 3000.0f));
				(*iter)->draw(shader);
			}

			iter++;
		}

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}

} }