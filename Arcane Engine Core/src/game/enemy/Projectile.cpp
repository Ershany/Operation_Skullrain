#include "Projectile.h"
#include <glm\glm.hpp>

namespace arcane {
	namespace game {

		/* Tree position is in terrain space (not world space) */

		Projectile::Projectile() {

		}

		Projectile::Projectile(graphics::Renderable3D *renderable) : Entity(renderable) {

		}

		void Projectile::update(float deltaTime) {
		}

		void Projectile::onRender() {

		}

		void Projectile::shoot() {
		}

		Cannon::Cannon() {

		}

		Cannon::Cannon(arcane::terrain::Terrain* terrain, graphics::Renderable3D *renderable, arcane::game::Player* player) {
			m_Terrain = terrain;
			m_Player = player;
			m_Renderable = renderable;
			//std::cout << "TEST" << std::endl;

			m_LifeLength = 20.0f;
			m_Born = glfwGetTime();
		}

		void Cannon::update(float deltaTime) {
			float playerToProjectileDistSquared = glm::length2(m_Player->getPosition() - m_Renderable->getPosition());

			if (playerToProjectileDistSquared < m_HullSize) {
				m_Player->hitPlayer(10.0f);
				//std::cout << "HERE" << std::endl;
				m_ShouldRemove = true;
				//TODO
				//Player Takes Damage
			}
			else if (glfwGetTime() > m_Born + m_LifeLength) {
				m_ShouldRemove = true;
			}
			else {
				glm::vec3 worldSpacePos = m_Terrain->getPosition() - m_Renderable->getPosition();

				float terrainHeight = m_Terrain->getVertexHeight(m_Renderable->getPosition().x / m_Terrain->getTerrainScale(), m_Renderable->getPosition().z / m_Terrain->getTerrainScale());
				m_Renderable->addPosition(glm::vec3(m_DirectionToMove.x, m_DirectionToMove.y, m_DirectionToMove.z));
			}
		}

	}
}