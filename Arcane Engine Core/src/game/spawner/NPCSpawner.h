#pragma once

#include "Spawner.h"
#include "../../terrain/Terrain.h"

namespace arcane { namespace game {

	class NPCSpawner : public Spawner {
	public:
		NPCSpawner(terrain::Terrain *terrain, int numNPCs);
	private:
		virtual void load() override;
	private:
		int m_NumNPCs;
	};

} }