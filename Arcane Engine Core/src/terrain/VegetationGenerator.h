#pragma once

#include <vector>
#include <stdlib.h>
#include <time.h>

#include "Terrain.h"
#include "../graphics/renderer/Renderable3D.h"

namespace arcane { namespace terrain {

	class VegetationGenerator {
	public:
		VegetationGenerator(Terrain *terrain, int numTrees);
		
		std::vector<graphics::Renderable3D*>::iterator getTreesBegin();
		std::vector<graphics::Renderable3D*>::iterator getTreesEnd();
	private:
		void load();
	private:
		Terrain *m_Terrain;

		std::vector<graphics::Renderable3D*> m_Trees;
		int m_NumTrees;
	};

} }