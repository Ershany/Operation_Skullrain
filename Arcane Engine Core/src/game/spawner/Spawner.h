#pragma once

#include "../../terrain/Terrain.h"
#include "../Entity.h"

#include <vector>

namespace arcane { namespace game {

	class Spawner {
	public:
		Spawner(terrain::Terrain *terrain);

		std::vector<Entity*>::iterator getBegin();
		std::vector<Entity*>::iterator getEnd();
		virtual void load() = 0;
	protected:
		terrain::Terrain *m_Terrain;

		std::vector<Entity*> m_Entities;
	};

} }