#pragma once

//Dependancies
#include "../../Dependancies.h"

//Operation Skullrain Headers
#include "../Entity.h"
#include "Projectile.h"
#include "../../graphics/Model.h"
#include "../Player.h"
#include "../../terrain/Terrain.h"
#include "../Entity.h"

namespace arcane {
	namespace game {
		namespace enemy {

			/* Tower position is in terrain space (not world space) */

			class Tower : public Entity {
			public:
				Tower(graphics::Renderable3D* renderable, arcane::graphics::Model* cannon, arcane::game::Player* player, std::vector<game::Entity*>* m_Entities, arcane::terrain::Terrain* terrain);

				void update(float deltaTime);
				void onRender();
				void shoot();

				std::vector<Projectile*> projectiles;
				arcane::graphics::Model* m_CannonBall;
				arcane::game::Player* m_Player;
				std::vector<game::Entity*>* m_Entities;
				arcane::terrain::Terrain* m_Terrain;

				float lastShotTime = glfwGetTime();
				float shotDelay = 3.00f;
				glm::vec3 m_Speed = glm::vec3(1.0f, 1.0f, 1.0f);
			};

		}
	}
}