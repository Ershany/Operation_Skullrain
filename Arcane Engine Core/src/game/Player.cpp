#include "Player.h"

namespace arcane { namespace game {

	Player::Player(graphics::Renderable3D *renderable, terrain::Terrain *terrain) : Entity(renderable), m_Terrain(terrain) {
		m_Velocity = glm::vec3(0.0f, 0.0f, 0.0f);
		m_TerminalVelocity = 2.0f;
		m_TerminalVelocitySquared = m_TerminalVelocity * m_TerminalVelocity;
		m_InitialFront = glm::vec3(0.0f, 0.0f, -1.0f);
		m_InitialUp = glm::vec3(0.0f, 1.0f, 0.0f);
		m_Orientation = glm::angleAxis(glm::radians(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		m_NPCPickupCount = 0;
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

		// Check if the helicopter landed
		glm::vec3 terrainSpacePos = m_Terrain->convertWorldToTerrainSpace(m_Renderable->getPosition());
		GLfloat terrainHeight = m_Terrain->getVertexHeight(terrainSpacePos.x / m_Terrain->getTerrainScale(), terrainSpacePos.z / m_Terrain->getTerrainScale());
		if (terrainHeight >= m_Renderable->getPosition().y) {
			m_Renderable->setPosition(glm::vec3(m_Renderable->getPosition().x, terrainHeight, m_Renderable->getPosition().z));
			m_Velocity.x = 0.0f; m_Velocity.y = 0.0f; m_Velocity.z = 0.0f;
			m_IsGrounded = true;
		}
		else {
			m_IsGrounded = false;
		}
	}

	void Player::pickupNPC() {
		++m_NPCPickupCount;
		std::cout << "Current NPC Pickup Count: " << m_NPCPickupCount << std::endl;
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
			m_Velocity += (m_Orientation  * -glm::normalize(glm::cross(m_InitialFront, m_InitialUp))) * deltaTime;
		}
		if (keycode == GLFW_KEY_D) {
			m_Velocity += (m_Orientation * glm::normalize(glm::cross(m_InitialFront, m_InitialUp))) * deltaTime;
		}
		if (keycode == GLFW_KEY_LEFT_CONTROL) {
			m_Velocity += (m_Orientation  * -m_InitialUp) * deltaTime;
		}
	}

} }