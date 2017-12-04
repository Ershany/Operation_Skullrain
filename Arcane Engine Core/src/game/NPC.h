#pragma once

//Dependancies
#include "../Dependancies.h"

//Operation Skullrain Headers
#include "Entity.h"
#include "Player.h"

namespace arcane { namespace game {

	/* NPC position is in terrain space (not world space) */

	class NPC : public Entity {
	public:
		NPC(graphics::Renderable3D *renderable, Player *player, terrain::Terrain *terrain);

		virtual void update(float deltaTime);
		virtual void onRender();
	private:
		Player *m_Player;
		terrain::Terrain *m_Terrain;

		float m_MaxRunSquared, m_MaxPickupSquared;
		glm::vec3 m_Speed;

		void runToPlayer(float deltaTime);
	};

} }