#include "NPCSpawner.h"

namespace arcane { namespace game {

	NPCSpawner::NPCSpawner(terrain::Terrain *terrain, int numNPCs, Player *player) : Spawner(terrain), m_Player(player) {
		m_NumNPCs = numNPCs;
		m_Entities.reserve(m_NumNPCs);
		srand(4);

		load();
	}

	void NPCSpawner::load() {
		glm::vec3 repositionVec = glm::vec3(0.0f, -20.0f, 0.0f);
		int borderBoundary = 2;

		graphics::Model *npcModel1 = new arcane::graphics::Model("res/3D_Models/Overwatch/McCree/McCree.obj");
		graphics::Model *npcModel2 = new arcane::graphics::Model("res/3D_Models/Overwatch/Reaper/Reaper.obj");

		for (unsigned int i = 0; i < m_NumNPCs; ++i) {
			float x = rand() % (m_Terrain->getVertexSideCount() - borderBoundary) + (borderBoundary / 2);
			float z = rand() % (m_Terrain->getVertexSideCount() - borderBoundary) + (borderBoundary / 2);

			glm::vec3 pos((x * m_Terrain->getTerrainScale()) + m_Terrain->getPosition().x, m_Terrain->getVertexHeight(x, z), (z * m_Terrain->getTerrainScale()) + m_Terrain->getPosition().z);
			pos += repositionVec;
			
			graphics::Model *npc;
			if (rand() & 1)
				npc = npcModel1;
			else
				npc = npcModel2;

			game::NPC *currentNPC = new game::NPC(new graphics::Renderable3D(pos, glm::vec3(0.07f, 0.07f, 0.07f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, npc, nullptr), m_Player, m_Terrain);

			m_Entities.push_back(currentNPC);
		}
	}

} }