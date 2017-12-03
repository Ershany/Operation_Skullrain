#pragma once

//Dependancies
#include "../../Dependancies.h"

//STL Includes
#include <vector>

//Operation Skullrain Headers
#include "../../terrain/Terrain.h"
#include "../Entity.h"

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