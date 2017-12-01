#pragma once

#include "Spawner.h"
#include "../NPC.h"
#include "../../terrain/Terrain.h"

namespace arcane { namespace game {

	class NPCSpawner : public Spawner {
	public:
		NPCSpawner(terrain::Terrain *terrain, int numNPCs, Player *player);
	private:
		virtual void load() override;
	private:
		int m_NumNPCs;
		Player *m_Player;
	};

} }