#include "Entity.h"

namespace arcane { namespace game {

	Entity::Entity(graphics::Renderable3D *renderable) {
		m_Renderable = renderable;
	}

	Entity::~Entity() {

	}

} }