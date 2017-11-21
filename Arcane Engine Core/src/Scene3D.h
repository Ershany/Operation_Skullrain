#pragma once

#include "graphics\renderer\Renderable3D.h"
#include "graphics\camera\Camera.h"
#include "graphics\renderer\Renderer.h"
#include "terrain\Terrain.h"
#include "graphics\Window.h"
#include "graphics\MeshFactory.h"
#include "graphics\Skybox.h"
#include "game\Player.h"
#include "terrain\VegetationGenerator.h"

namespace arcane {
	
	class Scene3D {
	private:
		graphics::Window *m_Window;
		graphics::Camera *m_Camera;
		graphics::Renderer *m_Renderer;
		terrain::Terrain *m_Terrain;
		terrain::VegetationGenerator *m_VegGenerator;
		graphics::MeshFactory m_meshFactory;
		graphics::Skybox *m_Skybox;

		game::Player *m_Player;

		// Some sort of list of entities (tied to models that are in the Renderer (Renderable3D) (should this name be changed to Renderer3D?))
		//std::vector<Entity*> m_Entities;
		std::vector<graphics::Renderable3D*> m_Renderables;

		graphics::Shader m_TerrainShader, m_ModelShader, m_OutlineShader, m_ModelReflectionShader;
	public:
		Scene3D(graphics::Camera *camera, graphics::Window *window);
		~Scene3D();
		
		void Add(graphics::Renderable3D *renderable);

		void onUpdate(double deltaTime);
		void onRender();

		void buttonPressed(unsigned int keycode);

		inline graphics::Renderer* getRenderer() const { return m_Renderer; }
		inline graphics::Camera* getCamera() const { return m_Camera; }
	private:
		void init();
	};

}