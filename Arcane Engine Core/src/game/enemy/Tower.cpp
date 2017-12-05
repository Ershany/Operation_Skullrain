#include "Tower.h"

namespace arcane {
	namespace game {
		namespace enemy {

			/* Tree position is in terrain space (not world space) */

			Tower::Tower(graphics::Renderable3D *renderable, arcane::graphics::Model* cannon, arcane::game::Player* player, std::vector<game::Entity*>* entities, arcane::terrain::Terrain *terrain) : Entity(renderable) {
				m_CannonBall = cannon;
				m_Player = player;
				m_Entities = entities;
				m_Terrain = terrain;
			}

			void Tower::update(float deltaTime) {
				if (glfwGetTime() - this->lastShotTime > this->shotDelay) {
					shoot();
				}

				for (int i = 0; i < projectiles.size(); i++) {
					Projectile* thisProjectile = projectiles.at(i);
					//thisProjectile->update();
				}
			}

			void Tower::onRender() {

			}

			void Tower::shoot() {
				glm::vec3 repositionVec = glm::vec3(0.0f, 12.0f, 0.0f);
				int borderBoundary = 2;

				float x = rand() % (m_Terrain->getVertexSideCount() - borderBoundary) + (borderBoundary / 2);
				float z = rand() % (m_Terrain->getVertexSideCount() - borderBoundary) + (borderBoundary / 2);

				glm::vec3 pos((x * m_Terrain->getTerrainScale()) + m_Terrain->getPosition().x, m_Terrain->getVertexHeight(x, z), (z * m_Terrain->getTerrainScale()) + m_Terrain->getPosition().z);
				pos += repositionVec;
				Projectile *new_projectile = new Cannon(m_Terrain, new graphics::Renderable3D(pos, glm::vec3(15.0f, 20.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, m_CannonBall, nullptr), m_Player);

				new_projectile->m_DirectionToMove = glm::normalize(m_Player->getPosition() - m_Renderable->getPosition()) * m_Speed;// *1.0f;

				m_Entities->push_back(new_projectile);
				this->projectiles.push_back(new_projectile);
			}

		}
	}
}