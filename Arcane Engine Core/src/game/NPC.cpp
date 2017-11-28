#include "NPC.h"

namespace arcane { namespace game {

	/* NPC position is in terrain space (not world space) */

	NPC::NPC(graphics::Renderable3D *renderable, Player *player, terrain::Terrain *terrain) 
		: Entity(renderable), m_Player(player), m_Speed(15.0f, 0.0f, 15.0f), m_Terrain(terrain) {
		m_MaxRunSquared = 125.0f * 125.0f;
		m_MaxPickupSquared = 20.0f * 20.0f;
	}

	void NPC::update(float deltaTime) {
		if (m_Player->isGrounded()) {
			float playerToNPCDistSquared = glm::length2(m_Player->getPosition() - m_Renderable->getPosition());

			if (playerToNPCDistSquared < m_MaxRunSquared) {
				runToPlayer(deltaTime);

				if (playerToNPCDistSquared < m_MaxPickupSquared) {
					m_ShouldRemove = true;
					m_Player->pickupNPC();
				}
			}
		}
	}

	void NPC::runToPlayer(float deltaTime) {
		glm::vec3 worldSpacePos = m_Terrain->getPosition() - m_Renderable->getPosition();
		glm::vec3 directionToMove = glm::normalize(m_Player->getPosition() - m_Renderable->getPosition()) * m_Speed * deltaTime;
		
		float terrainHeight = m_Terrain->getVertexHeight(m_Renderable->getPosition().x / m_Terrain->getTerrainScale(), m_Renderable->getPosition().z / m_Terrain->getTerrainScale());
		m_Renderable->addPosition(glm::vec3(directionToMove.x, 0.0f, directionToMove.z));
	}

} }