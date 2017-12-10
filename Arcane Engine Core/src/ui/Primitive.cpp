#include "Primitive.h"
#include <sstream>
#include <glm/glm.hpp>
#include <iostream>

namespace arcane { namespace ui {

	Primitive::Primitive(graphics::Window *window, GLuint texture) : m_TextureID(texture) {
		m_Window = window;
	}

	Primitive::~Primitive() {
	}

	void Primitive::draw(graphics::Shader &shader) {
	}

	Rect::Rect(graphics::Window *window, GLuint texture, GLfloat x, GLfloat y, GLfloat width, GLfloat height) : Primitive(window, texture) {
		this->x = y; this->y = y; this->width = width; this->height = height;

		GLfloat positions[] = {
			x,			y,			0.0f,
			x + width,  y,			0.0f,
			x,			y - height, 0.0f,
			x + width,  y - height, 0.0f
		};
		GLfloat uvs[] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f
		};
		GLuint indices[] = { 2, 1, 0, 2, 3, 1 };
		m_Ebo.load(indices, 6);
		m_Vao.addBuffer(new opengl::Buffer(positions, 3 * 4, 3), 0);
		m_Vao.addBuffer(new opengl::Buffer(uvs, 2 * 4, 2), 1);
	}

	void Rect::draw(graphics::Shader &shader) {
		glActiveTexture(GL_TEXTURE0);
		shader.setUniform1i("uiTexture", 0);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		m_Vao.bind();
		m_Ebo.bind();
		glDrawElements(GL_TRIANGLES, m_Ebo.getCount(), GL_UNSIGNED_INT, 0);
		m_Ebo.unbind();
		m_Vao.unbind();
	}

	HealthBar::HealthBar(graphics::Window *window, game::Player *player, GLuint texture, GLfloat x, GLfloat y, GLfloat width, GLfloat height) : Rect(window, texture, x, y, width, height) {
		m_Player = player;
	}

	void HealthBar::draw(graphics::Shader &shader) {
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_Player->getHealth() / m_Player->getMaxHealth(), 1.0f, 1.0f));
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f * (1 - m_Player->getHealth() / m_Player->getMaxHealth()), 0.0f, 0.0f));
		shader.setUniformMat4("model", translate * scale);

		Rect::draw(shader);
	}

	InvincibleBar::InvincibleBar(graphics::Window *window, game::Player *player, GLuint texture, GLfloat x, GLfloat y, GLfloat width, GLfloat height) : Rect(window, texture, x, y, width, height) {
		m_Player = player;
	}

	void InvincibleBar::draw(graphics::Shader &shader) {
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_Player->getInvincibleAmount() / m_Player->getMaxInvincibleAmount(), 1.0f, 1.0f));
		glm::mat4 translate = glm::mat4(1.0f);
		shader.setUniformMat4("model", translate * scale);

		Rect::draw(shader);
	}

} }