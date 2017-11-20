#pragma once

#include "Entity.h"

namespace arcane { namespace game {

	class Player : public Entity {
	public:
		Player(graphics::Renderable3D *renderable);
		~Player();

		virtual void update(double deltaTime) override;
	private:

	};

} }