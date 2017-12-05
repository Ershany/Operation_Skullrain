#pragma once

//Dependancies
#include "../Dependancies.h"

//STL Includes
#include <vector>
#include <stdlib.h>
#include <time.h>

//Operation Skullrain Headers
#include "Terrain.h"
#include "../game/spawner/Spawner.h"
#include "../graphics/renderer/Renderable3D.h"
#include "../game/Tree.h"

namespace arcane { namespace terrain {

	class VegetationSpawner : public game::Spawner {
	public:
		VegetationSpawner(Terrain *terrain, int numTrees);
	private:
		virtual void load() override;
		int m_NumTrees;
	};

} }