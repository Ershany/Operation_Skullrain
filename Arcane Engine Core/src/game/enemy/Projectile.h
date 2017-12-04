#pragma once

#include "../Entity.h"

namespace arcane {
	namespace game {
		namespace enemy {
			class Projectile : public Entity {
			public:
				Projectile();
				Projectile(graphics::Renderable3D *renderable);

				void update(float deltaTime);
				void onRender();
				void shoot();
			};

			class Cannon : public Projectile {
			public:
				Cannon();
				Cannon(glm::vec3& origin, arcane::graphics::Model* cannon);
			};

		}
	}
}