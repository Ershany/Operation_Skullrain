#include "VegetationGenerator.h"

namespace arcane { namespace terrain {

	VegetationGenerator::VegetationGenerator(Terrain *terrain, int numTrees) {
		m_Terrain = terrain;
		m_NumTrees = numTrees;
		m_Trees.reserve(m_NumTrees);
		srand(time(NULL));

		load();
	}

	std::vector<graphics::Renderable3D*>::iterator VegetationGenerator::getTreesBegin() {
		return m_Trees.begin();
	}

	std::vector<graphics::Renderable3D*>::iterator VegetationGenerator::getTreesEnd() {
		return m_Trees.end();
	}

	void VegetationGenerator::load() {
		glm::vec3 repositionVec = glm::vec3(0.0f, 12.0f, 0.0f);
		int borderBoundary = 2;

		graphics::Model *treeModel = new arcane::graphics::Model("res/3D_Models/Tree/lowpolytree.obj");

		for (unsigned int i = 0; i < m_NumTrees; ++i) {
			float x = rand() % (m_Terrain->getVertexSideCount() - borderBoundary) + (borderBoundary / 2);
			float z = rand() % (m_Terrain->getVertexSideCount() - borderBoundary) + (borderBoundary / 2);

			glm::vec3 pos(x * m_Terrain->getTerrainScale(), m_Terrain->getVertexHeight(x, z), z * m_Terrain->getTerrainScale());
			pos += repositionVec;
			graphics::Renderable3D *currentTree = new graphics::Renderable3D(pos, glm::vec3(15.0f, 20.0f, 15.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, treeModel);

			m_Trees.push_back(currentTree);
		}
	}

} }