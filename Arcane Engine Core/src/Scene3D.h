#pragma once

#include "graphics\renderer\Renderable3D.h"
#include "graphics\camera\Camera.h"
#include "graphics\renderer\Renderer.h"
#include "terrain\Terrain.h"
#include "graphics\Window.h"
#include "graphics\MeshFactory.h"
#include "graphics\Skybox.h"
#include "game\Player.h"
#include "terrain\VegetationSpawner.h"
#include "game\spawner\NPCSpawner.h"
#include "game\enemy\Enemy.h"
#include "utils\Timer.h"

namespace arcane {
	
	class Scene3D {
	public:
		Scene3D(graphics::Window *window);
		~Scene3D();
		
		void Add(game::Entity *entity);
		void Add(graphics::Renderable3D *renderable);

		void onUpdate(float deltaTime);
		void onRender();

		void buttonPressed(unsigned int keycode, float deltaTime);

		inline graphics::Renderer* getRenderer() const { return m_Renderer; }
		inline graphics::Camera* getCamera() const { return m_Camera; }
	private:
		void init();

		void Remove(game::Entity *entity);
		void Remove(graphics::Renderable3D *renderable);
	private:
		graphics::Window *m_Window;
		graphics::Camera *m_Camera;
		graphics::Renderer *m_Renderer;
		terrain::Terrain *m_Terrain;
		terrain::VegetationSpawner *m_VegSpawner;
		game::NPCSpawner *m_NPCSpawner;
		game::enemy::TowerSpawner *m_TowerSpawner;
		graphics::MeshFactory m_meshFactory;
		graphics::Skybox *m_Skybox;
		arcane::graphics::Model *m_CannonBall;

		arcane::Timer m_DeathAnimTime;
		bool m_PlayerRemoved;
		game::Player *m_Player;

		// List of entities and renderables. Entities are updated and rendered, but renderables are just rendered
		std::vector<game::Entity*> m_Entities;
		std::vector<graphics::Renderable3D*> m_Renderables;

		graphics::Shader m_TerrainShader, m_ModelShader, m_OutlineShader, m_PlayerShader;

		// Camera variables
		bool firstMove;
		GLfloat lastX;
		GLfloat lastY;
	};

}