#pragma once

#include "Entity.h"

namespace arcane { namespace game {

	class Tree : public Entity {
	public:
		Tree(graphics::Renderable3D *renderable);
	
		virtual void update(float deltaTime);
	};

} }