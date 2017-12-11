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

				lastShotTime = glfwGetTime();
				shotDelay = 1.00f;
				health = 50.0f;
			}

			void Tower::update(float deltaTime) {
				//std::cout << glfwGetTime() << std::endl;
				if (glfwGetTime() - this->lastShotTime > this->shotDelay) {
					//std::cout << "SHOOT" << std::endl;
					shoot();
					this->lastShotTime = glfwGetTime();
				}

				/*for (int i = 0; i < projectiles.size(); i++) {
					Projectile* thisProjectile = projectiles.at(i);
					thisProjectile->update(1.0f);
					if (thisProjectile->getShouldRemove()) {
						projectiles.erase(projectiles.begin() + i);
					}
				}*/
			}

			void Tower::onRender() {

			}

			void Tower::shoot() {
				//glm::vec3 repositionVec = glm::vec3(0.0f, 12.0f, 0.0f);
				int borderBoundary = 2;

				float x = m_Renderable->getPosition().x;
				float z = m_Renderable->getPosition().z;

				glm::vec3 pos(x, m_Terrain->getVertexHeight(x, z), z);
				//pos += repositionVec;
				Cannon *new_projectile = new Cannon(m_Terrain, new graphics::Renderable3D(pos, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, m_CannonBall, nullptr), m_Player);

				new_projectile->m_DirectionToMove = glm::normalize(m_Player->getPosition() - m_Renderable->getPosition()) * m_Speed;// *1.0f;

				m_Entities->push_back(new_projectile);
				//this->projectiles.push_back(new_projectile);
			}

		}
	}
}