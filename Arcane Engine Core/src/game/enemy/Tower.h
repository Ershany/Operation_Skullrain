#pragma once

#include "../Entity.h"

namespace arcane {
	namespace game {
		namespace enemy {

			/* Tower position is in terrain space (not world space) */

			class Tower : public Entity {
			public:
				Tower(graphics::Renderable3D *renderable);

				virtual void update(float deltaTime);
				virtual void onRender();
			};

		}
	}
}