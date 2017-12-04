#pragma once

//Dependancies
//#include "../../../

//STL Includes
#include <string>
#include <vector>

#include "../../terrain/Terrain.h"
#include "../spawner/Spawner.h"
#include "../enemy/Tower.h"

namespace arcane {
	namespace game {
		namespace enemy {
			class Enemy {
			public:
				Enemy();

				//virtual void draw();
			};

			class TowerSpawner : public Enemy, public Spawner {
			public:
				int x, y, width, height;
				int m_NumTowers;

				TowerSpawner(arcane::terrain::Terrain *terrain, int numTrees, arcane::graphics::Model* cannon);

				void load();
			};

		}
	}
}