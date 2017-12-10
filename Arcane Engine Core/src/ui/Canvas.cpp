#include "Canvas.h"
#include <sstream>
#include <iostream>

namespace arcane { namespace ui {

	Canvas::Canvas(graphics::Window *window, game::Player *player) : m_UIShader("src/shaders/UI.vert", "src/shaders/UI.frag") {
		m_Window = window;
		m_Player = player;

		m_HealthBar = new ui::HealthBar(window, player, opengl::Utility::loadTextureFromFile("res/textures/healthbar.png"), -1.0f, 1.0f, 1.0f, 0.05f); // Top left
		m_Primitives.push_back(m_HealthBar);

		m_InvincibleBar = new ui::InvincibleBar(window, player, opengl::Utility::loadTextureFromFile("res/textures/invinciblebar.png"), 0.0f, 1.0f, 1.0f, 0.05f); // Top right
		m_Primitives.push_back(m_InvincibleBar);
	}

	void Canvas::draw() {
		m_UIShader.enable();

		auto iter = m_Primitives.begin();
		while (iter != m_Primitives.end()) {
			m_UIShader.setUniformMat4("model", glm::mat4(1.0f));
			(*iter)->draw(m_UIShader);
			iter++;
		}
	}

} }