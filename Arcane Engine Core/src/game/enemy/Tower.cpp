#include "Tower.h"
#include <GLFW\glfw3.h>

namespace arcane {
	namespace game {
		namespace enemy {

			/* Tree position is in terrain space (not world space) */

			Tower::Tower(graphics::Renderable3D *renderable, arcane::graphics::Model* cannon, arcane::game::Player* player) : Entity(renderable) {
				m_CannonBall = cannon;
				m_Player = player;
			}

			void Tower::update(float deltaTime) {
				if (glfwGetTime() - this->lastShotTime > this->shotDelay) {
					shoot();
				}

				for (int i = 0; i < projectiles.size(); i++) {
					Projectile* thisProjectile = projectiles.at(i);
					thisProjectile->update();
				}
			}

			void Tower::onRender() {

			}

			void Tower::shoot() {
				Projectile *new_projectile = new Cannon(m_Player->getPosition, m_CannonBall);
				this->projectiles.push_back(new_projectile);
				m_Scene->Add(new_projectile);
				arcane::game::

			}

		}
	}
}