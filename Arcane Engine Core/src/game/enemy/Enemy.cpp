#include "Enemy.h"
#include <sstream>
#include <glm/glm.hpp>
#include <iostream>

#include "../../terrain/Terrain.h"
#include "../Entity.h"

namespace arcane {
	namespace game {
		Enemy::Enemy(arcane::terrain::Terrain *terrain) : game::Spawner(terrain) {
		}

		TowerSpawner::TowerSpawner(arcane::terrain::Terrain *terrain, int numTowers, arcane::graphics::Model* cannon, arcane::game::Player* player, std::vector<game::Entity*>* entities) : Enemy(terrain) {
			m_NumTowers = numTowers;
			m_Player = player;
			m_CannonBall = cannon;
			m_Entities = entities;

			m_Entities->reserve(m_NumTowers);
			srand(3);

			load();
		}

		void TowerSpawner::load() {
			glm::vec3 repositionVec = glm::vec3(0.0f, 12.0f, 0.0f);
			int borderBoundary = 2;

			graphics::Model *towerModel = new arcane::graphics::Model("res/3D_Models/Tower/tower.obj");

			for (unsigned int i = 0; i < m_NumTowers; ++i) {
				float x = rand() % (m_Terrain->getVertexSideCount() - borderBoundary) + (borderBoundary / 2);
				float z = rand() % (m_Terrain->getVertexSideCount() - borderBoundary) + (borderBoundary / 2);

				glm::vec3 pos((x * m_Terrain->getTerrainScale()) + m_Terrain->getPosition().x, m_Terrain->getVertexHeight(x, z), (z * m_Terrain->getTerrainScale()) + m_Terrain->getPosition().z);
				pos += repositionVec;
				game::enemy::Tower *currentTower = new game::enemy::Tower(new graphics::Renderable3D(pos, glm::vec3(15.0f, 20.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, towerModel, nullptr), m_CannonBall, m_Player, m_Entities);

				m_Entities->push_back(currentTower);
			}
		}

		void TowerSpawner::update() {

		}

		void TowerSpawner::onRender() {

		}
	};

}