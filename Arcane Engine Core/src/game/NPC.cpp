#include "NPC.h"

namespace arcane { namespace game {

	NPC::NPC(graphics::Renderable3D *renderable, Player *player) : Entity(renderable), m_Player(player) {}

	void NPC::update(float deltaTime) {

	}

} }