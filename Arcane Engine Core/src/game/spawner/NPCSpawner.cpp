#include "NPCSpawner.h"

namespace arcane { namespace game {

	NPCSpawner::NPCSpawner(terrain::Terrain *terrain, int numNPCs) : Spawner(terrain) {
		m_NumNPCs = numNPCs;

		load();
	}

	void NPCSpawner::load() {

	}

} }