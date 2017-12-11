#include "Player.h"

namespace arcane { namespace game {

	Player::Player(graphics::Renderable3D *renderable, graphics::Renderable3D *main_rotor, graphics::Renderable3D *back_rotor, terrain::Terrain *terrain, bool *firing)
			: Entity(renderable), m_Terrain(terrain), m_MaxRotorRotationAmount(0.4f), m_MinRotorRotationAmount(0.1f) {
		m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		m_TerminalVelocity = 10.0f;
		m_TerminalVelocitySquared = m_TerminalVelocity * m_TerminalVelocity;
		m_InitialFront = glm::vec3(0.0f, 0.0f, -1.0f);
		m_InitialUp = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Orientation = glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		m_CurrentRotorRotationAmount = m_MaxRotorRotationAmount;

		m_NPCPickupCount = 0;
		m_MaxHealth = 100.0f;
		m_Health = m_MaxHealth;
		m_MaxInvincibleAmount = 10.0f;
		m_InvincibleAmount = m_MaxInvincibleAmount;
		m_Tilt = 0.0f;
		m_IsDead = false;
		m_IsInvincible = false;

		m_MainRotor = main_rotor;
		m_BackRotor = back_rotor;

		m_firing = firing;
	}

	Player::~Player() {

	}

	void Player::update(float deltaTime) {
		// Check if the player is dead
		if (m_IsDead) {
			m_Velocity.x = 0.0f; m_Velocity.y = 0.0f; m_Velocity.z = 0.0f;
		}

		// Update invincibleAmount
		updateInvincible(deltaTime);

		// Apply rotations
		m_Renderable->addPosition(m_Velocity);
		//m_Renderable->compositeRotation(glm::angleAxis(0.25f * deltaTime, glm::vec3(3.0f - m_MainTilt, 0.0f, 3.0f - m_SideTilt)));
		m_Renderable->compositeRotation(glm::angleAxis(0.25f * deltaTime, glm::vec3(0.0f, 0.0f, 0.0f)));
		m_Orientation = glm::angleAxis(0.25f * deltaTime, glm::vec3(0.0f, 0.0f, 0.0f)) * m_Orientation;

		m_MainRotor->compositeRotation(glm::angleAxis(m_CurrentRotorRotationAmount * deltaTime, glm::vec3(0.0f, 70.0f, 0.0f)));
		m_BackRotor->compositeRotation(glm::angleAxis(m_CurrentRotorRotationAmount * deltaTime, glm::vec3(-70.0f, 0.0f, 0.0f)));

		// Restrict vector size
		if (glm::length2(m_Velocity) > m_TerminalVelocitySquared) {
			m_Velocity = glm::normalize(m_Velocity) * m_TerminalVelocity;
		}

		// Check if the helicopter landed 
		glm::vec3 terrainSpacePos = m_Terrain->convertWorldToTerrainSpace(m_Renderable->getPosition());
		GLfloat terrainHeight = m_Terrain->getVertexHeight(terrainSpacePos.x / m_Terrain->getTerrainScale(), terrainSpacePos.z / m_Terrain->getTerrainScale());

		float heliHeightCorrection = 10.0f;
		if (terrainHeight >= m_Renderable->getPosition().y + heliHeightCorrection) {
			m_Renderable->setPosition(glm::vec3(m_Renderable->getPosition().x, terrainHeight - heliHeightCorrection, m_Renderable->getPosition().z));
			m_Velocity.x = 0.0f; m_Velocity.y = 0.0f; m_Velocity.z = 0.0f;
			m_IsGrounded = true;

			// Rotar rotation decrease
			m_CurrentRotorRotationAmount -= 0.1f * deltaTime;
			if (m_CurrentRotorRotationAmount < m_MinRotorRotationAmount) {
				m_CurrentRotorRotationAmount = m_MinRotorRotationAmount;
			}
		}
		else {
			m_IsGrounded = false;

			// Rotar rotation increase
			m_CurrentRotorRotationAmount += 0.2f * deltaTime;
			if (m_CurrentRotorRotationAmount > m_MaxRotorRotationAmount) {
				m_CurrentRotorRotationAmount = m_MaxRotorRotationAmount;
			}
		}
	}

	void Player::onRender() {
		
	}

	void Player::pickupNPC() {
		++m_NPCPickupCount;
		std::cout << "Current NPC Pickup Count: " << m_NPCPickupCount << std::endl;
	}

	void Player::hitPlayer(float damage) {
		if (m_IsInvincible) {
			return;
		}

		m_Health -= damage;
		if (m_Health <= 0.0f) {
			killPlayer();
			m_Health = 0.0f;
		}
	}

	void Player::killPlayer() {
		m_IsDead = true;
		m_Velocity.x = 0.0f; m_Velocity.y = 0.0f; m_Velocity.z = 0.0f;
	}

	void Player::updateInvincible(float deltaTime) {
		if (m_IsInvincible) {
			m_InvincibleAmount -= deltaTime;
			if (m_InvincibleAmount < 0.0f) {
				m_InvincibleAmount = 0.0f;
				m_IsInvincible = false;
			}
		}
		else {
			m_InvincibleAmount += deltaTime;
			if (m_InvincibleAmount > m_MaxInvincibleAmount) {
				m_InvincibleAmount = m_MaxInvincibleAmount;
			}
		}
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


		if (keycode == GLFW_KEY_2 && m_InvincibleAmount > m_MaxInvincibleAmount * 0.1f) {
			m_IsInvincible = true;
		}

		// Debug controls
		if (keycode == GLFW_KEY_K) {
			hitPlayer(1.0f);
		}

		if (keycode == GLFW_KEY_1) {
			*m_firing = true;
		}
	}

} }