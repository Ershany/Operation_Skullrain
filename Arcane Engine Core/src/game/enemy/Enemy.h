#pragma once

//Dependancies
//#include "../../../

//STL Includes
#include <string>
#include <vector>

#include "../spawner/Spawner.h"

namespace arcane {
	namespace ui {
		struct Enemy {
			Enemy();

			virtual void draw();
		};

		struct Tower : public Enemy, public game::Spawner {
			int x, y, width, height;
			int numTowers;

			Tower(Terrain *terrain, int numTrees);
			Tower(int x, int y);

			void draw();
			void load();
		};

	}
}