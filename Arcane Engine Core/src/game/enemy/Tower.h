#pragma once

#include "../Entity.h"
#include "Projectile.h"
#include "../../graphics/Model.h"
#include "../Player.h"
#include "../Entity.h"

#include <vector>

namespace arcane {
	namespace game {
		namespace enemy {

			/* Tower position is in terrain space (not world space) */

			class Tower : public Entity {
			public:
				Tower(graphics::Renderable3D *renderable, arcane::graphics::Model* cannon, arcane::game::Player* player, std::vector<game::Entity*>* m_Entities);

				void update(float deltaTime);
				void onRender();
				void shoot();

				std::vector<Projectile*> projectiles;
				arcane::graphics::Model* m_CannonBall;
				arcane::game::Player* m_Player;
				std::vector<game::Entity*>* m_Entities;

				float lastShotTime;
				float shotDelay = 3.00f;
			};

		}
	}
}