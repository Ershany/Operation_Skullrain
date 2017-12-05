#pragma once

//Dependancies
#include "../../Dependancies.h"

//STL Includes
#include <string>
#include <vector>

//Operation Skullrain Headers
#include "../../terrain/Terrain.h"
#include "../spawner/Spawner.h"
#include "../enemy/Tower.h"
#include "../Player.h"
#include "../../graphics/Model.h"
#include "../Entity.h"

namespace arcane {
	namespace game {
		class Enemy : public Entity, public Spawner {
		public:
			Enemy(arcane::terrain::Terrain *terrain);

			//virtual void draw();
		};

		class TowerSpawner : public Enemy {
		public:
			int x, y, width, height;
			int m_NumTowers;
			arcane::graphics::Model* m_CannonBall;
			arcane::game::Player* m_Player;
			std::vector<game::Entity*>* m_Entities;
			arcane::terrain::Terrain* m_Terrain;

			TowerSpawner(arcane::terrain::Terrain *terrain, int numTrees, arcane::graphics::Model* cannon, arcane::game::Player* player, std::vector<game::Entity*>* entities);

			void update(float deltaTime);
			void onRender();

			void load();
		};

	}
}