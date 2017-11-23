#include "Player.h"

namespace arcane { namespace game {

	Player::Player(graphics::Renderable3D *renderable) : Entity(renderable) {
		m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
		m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Orientation = glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	Player::~Player() {

	}

	void Player::update(float deltaTime) {
		m_Renderable->addPosition(m_Velocity);
		m_Renderable->compositeRotation(glm::angleAxis(0.01f, glm::vec3(0.0f, 1.0f, 0.0f)));
	}

	void Player::buttonPressed(unsigned int keycode, float deltaTime) {
		if (keycode == GLFW_KEY_SPACE) {
			m_Velocity += (m_Orientation * m_Up) * deltaTime;
		}
		if (keycode == GLFW_KEY_W) {
			m_Velocity += (m_Orientation * m_Front) * deltaTime;
		}
		if (keycode == GLFW_KEY_S) {
			m_Velocity += (m_Orientation  * -m_Front) * deltaTime;
		}
		if (keycode == GLFW_KEY_A) {
			m_Velocity += (m_Orientation  * -glm::cross(m_Front, m_Up)) * deltaTime;
		}
		if (keycode == GLFW_KEY_D) {
			m_Velocity += (m_Orientation * glm::cross(m_Front, m_Up)) * deltaTime;
		}
		if (keycode == GLFW_KEY_LEFT_CONTROL) {
			m_Velocity += (m_Orientation  * -m_Up) * deltaTime;
		}
	}

} }