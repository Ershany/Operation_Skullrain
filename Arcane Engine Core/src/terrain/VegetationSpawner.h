#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>

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
	private:
		int m_NumTrees;
	};

} }