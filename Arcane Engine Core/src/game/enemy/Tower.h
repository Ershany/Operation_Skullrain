#pragma once

#include "../Entity.h"
#include "Projectile.h"
#include "../../graphics/Model.h"

#include <vector>

namespace arcane {
	namespace game {
		namespace enemy {

			/* Tower position is in terrain space (not world space) */

			class Tower : public Entity {
			public:
				Tower(graphics::Renderable3D *renderable);

				void update(float deltaTime);
				void onRender();
				void shoot();

				std::vector<Projectile> projectiles;
			};

		}
	}
}