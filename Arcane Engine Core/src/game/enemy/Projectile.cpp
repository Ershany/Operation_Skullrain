#include "Projectile.h"

namespace arcane {
	namespace game {
		namespace enemy {

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
				float x = rand() % (m_Terrain->getVertexSideCount() - borderBoundary) + (borderBoundary / 2);
				float z = rand() % (m_Terrain->getVertexSideCount() - borderBoundary) + (borderBoundary / 2);

				glm::vec3 pos((x * m_Terrain->getTerrainScale()) + m_Terrain->getPosition().x, m_Terrain->getVertexHeight(x, z), (z * m_Terrain->getTerrainScale()) + m_Terrain->getPosition().z);
				pos += repositionVec;
				game::enemy::Tower *currentTree = new game::enemy::Tower(new graphics::Renderable3D(pos, glm::vec3(15.0f, 20.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, towerModel, nullptr));
				
				glm::vec3 m_DirectionToMove = glm::normalize(m_Player->getPosition() - m_Renderable->getPosition()) * m_Speed * deltaTime;
				
				m_Entities.push_back(currentTree);
			}

			Cannon::Cannon() {

			}

			Cannon::Cannon(glm::vec3& origin, arcane::graphics::Model* cannon) {

			}
			
			Cannon::update(float deltaTime) {
				float playerToProjectileDistSquared = glm::length2(m_Scene->getPlayer->getPosition() - m_Renderable->getPosition());

				if (playerToNPCDistSquared < m_HullSize) {
					m_ShouldRemove = true;
					//TODO
					//Player Takes Damage
				}
				else {
					glm::vec3 worldSpacePos = m_Terrain->getPosition() - m_Renderable->getPosition();

					float terrainHeight = m_Terrain->getVertexHeight(m_Renderable->getPosition().x / m_Terrain->getTerrainScale(), m_Renderable->getPosition().z / m_Terrain->getTerrainScale());
					m_Renderable->addPosition(glm::vec3(directionToMove.x, 0.0f, directionToMove.z));
				}
			}

		}
	}
}