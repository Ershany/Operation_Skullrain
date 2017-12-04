#pragma once

#include "../Entity.h"
#include "../../graphics/renderer/Renderable3D.h"

namespace arcane {
	namespace game {
		namespace enemy {
			class Projectile : public Entity {
			public:
				Projectile();
				Projectile(graphics::Renderable3D *renderable);

				virtual void update(float deltaTime);
				void onRender();
				void shoot();

				inline graphics::Renderable3D* getRenderable() const { return m_Renderable; }

				float m_DirectionToMove;
			};

			class Cannon : public Projectile {
			public:
				Cannon();
				Cannon(glm::vec3& origin, arcane::graphics::Model* cannon);
				void update(float deltatime);

				float m_HullSize = 10;
			};

		}
	}
}