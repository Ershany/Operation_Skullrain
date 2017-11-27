#pragma once

#include "Entity.h"
#include "Player.h"

namespace arcane { namespace game {

	class NPC : public Entity {
	public:
		NPC(graphics::Renderable3D *renderable, Player *player);

		virtual void update(float deltaTime);
	private:
		Player *m_Player;
	};

} }