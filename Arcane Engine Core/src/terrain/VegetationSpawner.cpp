#include "VegetationSpawner.h"

namespace arcane { namespace terrain {

	VegetationSpawner::VegetationSpawner(Terrain *terrain, int numTrees) : game::Spawner(terrain) {
		m_NumTrees = numTrees;
		m_Entities.reserve(m_NumTrees);
		srand(3);

		load();
	}

	void VegetationSpawner::load() {
		glm::vec3 repositionVec = glm::vec3(0.0f, 12.0f, 0.0f);
		int borderBoundary = 2;

		graphics::Model *treeModel = new arcane::graphics::Model("res/3D_Models/Tree/lowpolytree.obj");

		for (unsigned int i = 0; i < m_NumTrees; ++i) {
			float x = rand() % (m_Terrain->getVertexSideCount() - borderBoundary) + (borderBoundary / 2);
			float z = rand() % (m_Terrain->getVertexSideCount() - borderBoundary) + (borderBoundary / 2);

			glm::vec3 pos((x * m_Terrain->getTerrainScale()) + m_Terrain->getPosition().x, m_Terrain->getVertexHeight(x, z), (z * m_Terrain->getTerrainScale()) + m_Terrain->getPosition().z);
			pos += repositionVec;
			game::Tree *currentTree = new game::Tree(new graphics::Renderable3D(pos, glm::vec3(15.0f, 20.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, treeModel));

			m_Entities.push_back(currentTree);
		}
	}

} }