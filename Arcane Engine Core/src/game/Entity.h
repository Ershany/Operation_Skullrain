#pragma once

#include <glm\common.hpp>

#include "../graphics/renderer/Renderable3D.h"

namespace arcane { namespace game {

	class Entity {
	public:
		Entity(graphics::Renderable3D *renderable);
		virtual ~Entity();

		virtual void update(float deltaTime) = 0;

		inline glm::vec3 getPosition() { return m_Renderable->getPosition(); }
		inline graphics::Renderable3D* getRenderable() { return m_Renderable; }
		inline bool getShouldRemove() { return m_ShouldRemove; }
	protected:
		graphics::Renderable3D *m_Renderable;
		bool m_ShouldRemove;
	};

} }