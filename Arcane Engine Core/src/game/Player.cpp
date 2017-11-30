#include "Player.h"

namespace arcane { namespace game {

	Player::Player(graphics::Renderable3D *renderable, graphics::Renderable3D *main_rotor, graphics::Renderable3D *back_rotor) : Entity(renderable) {
		m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		m_TerminalVelocity = 10.0f;
		m_TerminalVelocitySquared = m_TerminalVelocity * m_TerminalVelocity;
		m_InitialFront = glm::vec3(0.0f, 0.0f, -1.0f);
		m_InitialUp = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Orientation = glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		m_Tilt = 0.0f;

		m_MainRotor = main_rotor;
		m_BackRotor = back_rotor;
	}

	Player::~Player() {

	}

	void Player::update(float deltaTime) {
		m_Renderable->addPosition(m_Velocity);
		//m_Renderable->compositeRotation(glm::angleAxis(0.25f * deltaTime, glm::vec3(3.0f - m_MainTilt, 0.0f, 3.0f - m_SideTilt)));
		m_Renderable->compositeRotation(glm::angleAxis(0.25f * deltaTime, glm::vec3(0.0f, 0.0f, 0.0f)));
		m_Orientation = glm::angleAxis(0.25f * deltaTime, glm::vec3(0.0f, 0.0f, 0.0f)) * m_Orientation;

		//std::cout << m_Tilt << std::endl;

		m_MainRotor->compositeRotation(glm::angleAxis(0.25f * deltaTime, glm::vec3(0.0f, 70.0f, 0.0f)));
		m_BackRotor->compositeRotation(glm::angleAxis(0.25f * deltaTime, glm::vec3(-70.0f, 0.0f, 0.0f)));

		// Restrict vector size
		if (glm::length2(m_Velocity) > m_TerminalVelocitySquared) {
			m_Velocity = glm::normalize(m_Velocity) * m_TerminalVelocity;
		}

		///std::cout << m_MainTilt << std::endl;
		///std::cout << m_MainTilt << std::endl;
		///std::cout << m_MainTilt << std::endl;
	}

	void Player::buttonPressed(unsigned int keycode, float deltaTime) {
		if (keycode == GLFW_KEY_SPACE) {
			m_Velocity += (m_Orientation * m_InitialUp) * deltaTime;
		}
		if (keycode == GLFW_KEY_W) {
			m_Velocity += (m_Orientation * m_InitialFront) * deltaTime;
			m_MainTilt += 1.0f;
		}
		if (keycode == GLFW_KEY_S) {
			m_Velocity += (m_Orientation  * -m_InitialFront) * deltaTime;
			m_MainTilt += -1.0f;
		}
		if (keycode == GLFW_KEY_A) {
			m_Renderable->compositeRotation(glm::angleAxis(0.25f * deltaTime, glm::vec3(0.0f, 2.0f, 0.0f)));
			m_Orientation = glm::angleAxis(0.25f * deltaTime, glm::vec3(0.0f, 2.0f, 0.0f)) * m_Orientation;
			m_SideTilt += 1.0f;
		}
		if (keycode == GLFW_KEY_D) {
			m_Renderable->compositeRotation(glm::angleAxis(0.25f * deltaTime, glm::vec3(0.0f, -2.0f, 0.0f)));
			m_Orientation = glm::angleAxis(0.25f * deltaTime, glm::vec3(0.0f, -2.0f, 0.0f)) * m_Orientation;
			m_SideTilt += -1.0f;
		}
		if (keycode == GLFW_KEY_LEFT_CONTROL) {
			m_Velocity += (m_Orientation  * -m_InitialUp) * deltaTime;
		}

		m_MainTilt += (0.5f * m_MainTilt);
		m_SideTilt += (0.5f * m_SideTilt);
	}

} }