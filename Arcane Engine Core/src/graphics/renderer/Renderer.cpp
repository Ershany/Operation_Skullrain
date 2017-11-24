#include "Renderer.h"

namespace arcane { namespace graphics {

	Renderer::Renderer(Camera *camera) : m_Camera(camera)
	{ 
	}

	void Renderer::submitOpaque(Renderable3D *renderable) {
		m_OpaqueRenderQueue.push_back(renderable);
	}

	void Renderer::submitTransparent(Renderable3D *renderable) {
		m_TransparentRenderQueue.push_back(renderable);
	}

	void Renderer::flushOpaque(Shader &shader, Shader &outlineShader) {
		glEnable(GL_CULL_FACE);

		// Render opaque objects
		while (!m_OpaqueRenderQueue.empty()) {
			// Drawing prepration
			glEnable(GL_DEPTH_TEST);
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);

			Renderable3D *current = m_OpaqueRenderQueue.front();

			// Draw the renderable 3d
			glm::mat4 model(1);
			glm::mat4 translate = glm::translate(glm::mat4(1.0f), current->getPosition());
			glm::mat4 rotate = glm::toMat4(current->getOrientation());
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), current->getScale());

			if (current->getParent != nullptr) {
				model = translate * rotate * scale;
			}
			else {
				model = current->getParent.getPosition * current->getParent.getOrientation * translate * rotate * scale;
			}

			shader.setUniformMat4("model", model);
			current->draw(shader);

			// Draw the outline
			if (current->getShouldOutline()) {
				glStencilFunc(GL_NOTEQUAL, 1, 0xFF);

				outlineShader.enable();
				body = glm::mat4(1);
				translate = glm::translate(glm::mat4(1.0f), current->getPosition());
				rotate = glm::toMat4(current->getOrientation());
				scale = glm::scale(glm::mat4(1.0f), current->getScale() + glm::vec3(0.025f, 0.025f, 0.025f));
				body = translate * rotate * scale;
				outlineShader.setUniformMat4("model", body);
				current->draw(outlineShader);
				outlineShader.disable();

				glEnable(GL_DEPTH_TEST);
				glStencilMask(0xFF);

				shader.enable();

				glClear(GL_STENCIL_BUFFER_BIT);
			}

			m_OpaqueRenderQueue.pop_front();
		}
	}

	void Renderer::flushTransparent(Shader &shader, Shader &outlineShader) {
		glDisable(GL_CULL_FACE); // Don't backface cull transparent objects

		// Sort then render transparent objects (from back to front, does not account for rotations or scaling)
		std::sort(m_TransparentRenderQueue.begin(), m_TransparentRenderQueue.end(),
			[this](Renderable3D *a, Renderable3D *b) -> bool
		{
			return glm::length2(m_Camera->getPosition() - a->getPosition()) > glm::length2(m_Camera->getPosition() - b->getPosition());
		});
		while (!m_TransparentRenderQueue.empty()) {
			// Drawing prepration
			glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);

			// Enable blending (note: You will still need to sort from back to front when rendering)
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Tell OpenGL how to blend, in this case make the new object have the transparency of its alpha and the object in the back is 1-alpha

			Renderable3D *current = m_TransparentRenderQueue.front();
			
			// Draw the renderable 3d
			glm::mat4 model(1);
			glm::mat4 translate = glm::translate(glm::mat4(1.0f), current->getPosition());
			glm::mat4 rotate = glm::toMat4(current->getOrientation());
			glm::mat4 scale = glm::scale(glm::mat4(1.0f), current->getScale());
			model = translate * rotate * scale;
			shader.setUniformMat4("model", model);
			current->draw(shader);

			// Draw the outline
			if (current->getShouldOutline()) {
				glStencilFunc(GL_NOTEQUAL, 1, 0xFF);

				outlineShader.enable();
				model = glm::mat4(1);
				translate = glm::translate(glm::mat4(1.0f), current->getPosition());
				rotate = glm::toMat4(current->getOrientation());
				scale = glm::scale(glm::mat4(1.0f), current->getScale() + glm::vec3(0.025f, 0.025f, 0.025f));
				model = translate * rotate * scale;
				outlineShader.setUniformMat4("model", model);
				current->draw(outlineShader);
				outlineShader.disable();

				glEnable(GL_DEPTH_TEST);
				glStencilMask(0xFF);

				shader.enable();

				glClear(GL_STENCIL_BUFFER_BIT);
			}

			glDisable(GL_BLEND);

			m_TransparentRenderQueue.pop_front();
		}
	}

} }