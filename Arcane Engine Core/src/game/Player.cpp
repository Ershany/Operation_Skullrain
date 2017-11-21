#include "Player.h"

namespace arcane { namespace game {

	Player::Player(graphics::Renderable3D *renderable) : Entity(renderable) {
		m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
	}

	Player::~Player() {

	}

	void Player::update(double deltaTime) {

	}

	void Player::buttonPressed(unsigned int keycode) {
		if (keycode == GLFW_KEY_SPACE) {
			m_Renderable->addPosition(glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (keycode == GLFW_KEY_LEFT_CONTROL) {
			m_Renderable->addPosition(glm::vec3(0.0f, -1.0f, 0.0f));
		}
	}

} }