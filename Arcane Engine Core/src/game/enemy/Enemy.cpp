#include "Enemy.h"
#include <sstream>
#include <glm/glm.hpp>
#include <iostream>

#include "Terrain.h"

namespace arcane {
	namespace ui {
		Enemy::Enemy() {
		}

		Tower::Tower(Terrain *terrain, int numTowers) {
			m_NumTowers = numTowers;
			m_Entities.reserve(m_NumTrees);
			srand(3);

			load();
		}

		void Tower::load() {
			glm::vec3 repositionVec = glm::vec3(0.0f, 12.0f, 0.0f);
			int borderBoundary = 2;

			graphics::Model *towerModel = new arcane::graphics::Model("res/3D_Models/Tower/tower.obj");

			for (unsigned int i = 0; i < m_NumTowers; ++i) {
				float x = rand() % (m_Terrain->getVertexSideCount() - borderBoundary) + (borderBoundary / 2);
				float z = rand() % (m_Terrain->getVertexSideCount() - borderBoundary) + (borderBoundary / 2);

				glm::vec3 pos((x * m_Terrain->getTerrainScale()) + m_Terrain->getPosition().x, m_Terrain->getVertexHeight(x, z), (z * m_Terrain->getTerrainScale()) + m_Terrain->getPosition().z);
				pos += repositionVec;
				game::Tree *currentTree = new game::Tree(new graphics::Renderable3D(pos, glm::vec3(15.0f, 20.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, treeModel, nullptr));

				m_Entities.push_back(currentTree);
			}
		}
	};

}