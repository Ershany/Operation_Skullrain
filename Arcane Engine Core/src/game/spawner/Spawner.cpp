#include "Spawner.h"

namespace arcane { namespace game {

	Spawner::Spawner(terrain::Terrain *terrain) : m_Terrain(terrain) {}

	std::vector<Entity*>::iterator Spawner::getBegin() {
		return m_Entities.begin();
	}
	
	std::vector<Entity*>::iterator Spawner::getEnd() {
		return m_Entities.end();
	}

} }