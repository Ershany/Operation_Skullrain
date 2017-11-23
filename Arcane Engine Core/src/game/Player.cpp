#include "Player.h"

namespace arcane { namespace game {

	Player::Player(graphics::Renderable3D *renderable) : Entity(renderable) {
		m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		m_TerminalVelocity = 2.0f;
		m_TerminalVelocitySquared = m_TerminalVelocity * m_TerminalVelocity;
		m_InitialFront = glm::vec3(0.0f, 0.0f, -1.0f);
		m_InitialUp = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Orientation = glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	}

	Player::~Player() {

	}

	void Player::update(float deltaTime) {
		m_Renderable->addPosition(m_Velocity);
		m_Renderable->compositeRotation(glm::angleAxis(0.25f * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f)));
		m_Orientation = glm::angleAxis(0.25f * deltaTime, glm::vec3(0.0f, 1.0f, 0.0f)) * m_Orientation;

		// Restrict vector size
		if (glm::length2(m_Velocity) > m_TerminalVelocitySquared) {
			m_Velocity = glm::normalize(m_Velocity) * m_TerminalVelocity;
		}
	}

	void Player::buttonPressed(unsigned int keycode, float deltaTime) {
		if (keycode == GLFW_KEY_SPACE) {
			m_Velocity += (m_Orientation * m_InitialUp) * deltaTime;
		}
		if (keycode == GLFW_KEY_W) {
			m_Velocity += (m_Orientation * m_InitialFront) * deltaTime;
		}
		if (keycode == GLFW_KEY_S) {
			m_Velocity += (m_Orientation  * -m_InitialFront) * deltaTime;
		}
		if (keycode == GLFW_KEY_A) {
			m_Velocity += (m_Orientation  * -glm::cross(m_InitialFront, m_InitialUp)) * deltaTime;
		}
		if (keycode == GLFW_KEY_D) {
			m_Velocity += (m_Orientation * glm::cross(m_InitialFront, m_InitialUp)) * deltaTime;
		}
		if (keycode == GLFW_KEY_LEFT_CONTROL) {
			m_Velocity += (m_Orientation  * -m_InitialUp) * deltaTime;
		}
	}

} }