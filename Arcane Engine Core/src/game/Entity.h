#pragma once

#include <glm\common.hpp>

#include "../graphics/renderer/Renderable3D.h"

namespace arcane { namespace game {

	class Entity {
	public:
		Entity(graphics::Renderable3D *renderable);
		~Entity();

		virtual void update(double deltaTime) = 0;


	protected:
		graphics::Renderable3D *m_Renderable;
	};

} }