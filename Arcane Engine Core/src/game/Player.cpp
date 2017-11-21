#include "Player.h"

namespace arcane { namespace game {

	Player::Player(graphics::Renderable3D *renderable) : Entity(renderable) {
		m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Front = glm::vec3(1.0f, 0.0f, 0.0f);
		m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
	}

	Player::~Player() {

	}

	void Player::update(double deltaTime) {

	}

	void Player::buttonPressed(unsigned int keycode) {
		if (keycode == GLFW_KEY_SPACE) {
			m_Renderable->addPosition(m_Up);
		}
		if (keycode == GLFW_KEY_W) {
			m_Renderable->addPosition(m_Front);
		}
		if (keycode == GLFW_KEY_S) {
			m_Renderable->addPosition(-m_Front);
		}
		if (keycode == GLFW_KEY_A) {
			m_Renderable->addPosition(-glm::cross(m_Front, m_Up));
		}
		if (keycode == GLFW_KEY_D) {
			m_Renderable->addPosition(glm::cross(m_Front, m_Up));
		}
		if (keycode == GLFW_KEY_LEFT_CONTROL) {
			m_Renderable->addPosition(-m_Up);
		}
	}

} }