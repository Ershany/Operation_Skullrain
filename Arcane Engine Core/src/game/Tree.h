#pragma once

#include "Entity.h"

namespace arcane { namespace game {
	
	/* Tree position is in terrain space (not world space) */

	class Tree : public Entity {
	public:
		Tree(graphics::Renderable3D *renderable);
	
		virtual void update(float deltaTime);
		virtual void onRender();
	};

} }