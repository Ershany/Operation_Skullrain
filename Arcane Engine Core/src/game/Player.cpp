#include "Player.h"

namespace arcane { namespace game {

	Player::Player(graphics::Renderable3D *renderable, graphics::Renderable3D *main_rotor, graphics::Renderable3D *back_rotor) : Entity(renderable) {
		m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		m_TerminalVelocity = 2.0f;
		m_TerminalVelocitySquared = m_TerminalVelocity * m_TerminalVelocity;
		m_InitialFront = glm::vec3(0.0f, 0.0f, -1.0f);
		m_InitialUp = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Orientation = glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		m_Tilt = 0.0f;
		m_Tilt = 0.0f;

		m_MainRotor = main_rotor;
		m_BackRotor = back_rotor;
	}

	Player::~Player() {

	}

	void Player::update(float deltaTime) {
		m_Renderable->addPosition(m_Velocity);
		m_Renderable->compositeRotation(glm::angleAxis(0.25f * deltaTime, glm::vec3(m_Tilt, 0.0f, 0.0f)));
		m_Orientation = glm::angleAxis(0.25f * deltaTime, glm::vec3(m_Tilt, 0.0f, 0.0f)) * m_Orientation;

		//std::cout << m_Tilt << std::endl;

		m_MainRotor->compositeRotation(glm::angleAxis(0.25f * deltaTime, glm::vec3(0.0f, 100.0f, 0.0f)));
		m_BackRotor->compositeRotation(glm::angleAxis(0.25f * deltaTime, glm::vec3(100.0f, 0.0f, 0.0f)));

		// Restrict vector size
		if (glm::length2(m_Velocity) > m_TerminalVelocitySquared) {
			m_Velocity = glm::normalize(m_Velocity) * m_TerminalVelocity;
		}
	}

	void Player::buttonPressed(unsigned int keycode, float deltaTime) {
		//Increase the rotation speed of the main rotor
		if (keycode == GLFW_KEY_SPACE) {
			m_Lift += (m_Orientation * m_InitialUp) * deltaTime;
		}
		if (keycode == GLFW_KEY_W) {
			m_Tilt += (3.0f - m_TiltAmount) * 0.3f;
			m_TiltAmount += m_Tilt;
		}
		if (keycode == GLFW_KEY_S) {
			m_Tilt += (-3.0f - m_TiltAmount) * 0.3f;
			m_TiltAmount += m_Tilt;
		}
		if (keycode == GLFW_KEY_A) {
			//m_RotorRotationAccel += 0.5f;
		}
		if (keycode == GLFW_KEY_D) {
			//m_RotorRotationAccel -= 0.5f;
		}
		if (keycode == GLFW_KEY_LEFT_CONTROL) {
			m_Lift += (m_Orientation  * -m_InitialUp) * deltaTime;
		}

		if (m_TiltAmount > 3.0f) {
			m_TiltAmount = 3.0f;
		}

		if (m_TiltAmount < -3.0f) {
			m_TiltAmount = -3.0f;
		}
		//m_RotorRotation += m_RotorRotationAccel;
		m_Velocity += m_Lift;
	}

} }