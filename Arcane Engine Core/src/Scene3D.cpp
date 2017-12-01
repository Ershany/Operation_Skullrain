#include "Scene3D.h"

#include <iterator>
#include <iostream>
#include <glm/glm.hpp>

namespace arcane {

	Scene3D::Scene3D(graphics::Window *window)
		: m_TerrainShader("src/shaders/basic.vert", "src/shaders/terrain.frag"), m_ModelShader("src/shaders/basic.vert", "src/shaders/model.frag"), m_Window(window),
		  m_OutlineShader("src/shaders/basic.vert", "src/shaders/basic.frag"), m_PlayerShader("src/shaders/basic.vert", "src/shaders/player.frag", "src/shaders/player.geom")
	{
		m_Camera = new graphics::Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
		m_Renderer = new graphics::Renderer(m_Camera);
		m_Terrain = new terrain::Terrain(glm::vec3(-1280.0f, -20.0f, -1280.0f)); // Make it so the center of the terrain is on the origin

		//Low poly heli
		//graphics::Renderable3D *player_helicopter_body = new graphics::Renderable3D(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f, 4.0f, 4.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(0.0f), new arcane::graphics::Model("res/3D_Models/Helicopter/body_low_poly.obj"), nullptr, false);
		graphics::Renderable3D *player_helicopter_body = new graphics::Renderable3D(glm::vec3(90.0f, -10.0f, 90.0f), glm::vec3(4.0f, 4.0f, 4.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(0.0f), new arcane::graphics::Model("res/3D_Models/Helicopter/body.obj"), nullptr, false, true);
		m_Player = new game::Player(player_helicopter_body,
			new graphics::Renderable3D(glm::vec3(0.0f, 6.5f, 0.0f), glm::vec3(4.0f, 4.0f, 4.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(0.0f), new arcane::graphics::Model("res/3D_Models/Helicopter/main_rotor.obj"), player_helicopter_body, false, false),
			new graphics::Renderable3D(glm::vec3(0.0f, 9.8f, 42.0f), glm::vec3(4.0f, 4.0f, 4.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(0.0f), new arcane::graphics::Model("res/3D_Models/Helicopter/back_rotor.obj"), player_helicopter_body, false, false), m_Terrain);
		m_VegSpawner = new terrain::VegetationSpawner(m_Terrain, 500);
		m_NPCSpawner = new game::NPCSpawner(m_Terrain, 20, m_Player);

		firstMove = true;
		lastX = m_Window->getMouseX();
		lastY = m_Window->getMouseY();

		init();
	}

	Scene3D::~Scene3D() {
		delete m_Camera;
		delete m_Renderer;
		delete m_Terrain;
		delete m_VegSpawner;
		delete m_NPCSpawner;
		delete m_Player;
		delete m_Skybox;
	}

	void Scene3D::init() {
		glEnable(GL_MULTISAMPLE);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		glEnable(GL_CULL_FACE);

		// Skybox
		std::vector<const char*> skyboxFilePaths;
		skyboxFilePaths.push_back("res/skybox/right.png");
		skyboxFilePaths.push_back("res/skybox/left.png");
		skyboxFilePaths.push_back("res/skybox/top.png");
		skyboxFilePaths.push_back("res/skybox/bottom.png");
		skyboxFilePaths.push_back("res/skybox/back.png");
		skyboxFilePaths.push_back("res/skybox/front.png");
		m_Skybox = new graphics::Skybox(skyboxFilePaths, m_Camera, m_Window);

		//Add(m_Player);
		Add(m_Player->getMainRotor());
		Add(m_Player->getBackRotor());

		auto vegIter = m_VegSpawner->getBegin();
		while (vegIter != m_VegSpawner->getEnd()) {
			Add(*vegIter);
			vegIter++;
		}

		auto npcIter = m_NPCSpawner->getBegin();
		while (npcIter != m_NPCSpawner->getEnd()) {
			Add(*npcIter);
			npcIter++;
		}

		// Terrain shader
		m_TerrainShader.enable();
		m_TerrainShader.setUniform1f("material.shininess", 128.0f);
		m_TerrainShader.setUniform3f("dirLight.direction", glm::vec3(0.0f, -1.0f, 0.0f));
		m_TerrainShader.setUniform3f("dirLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
		m_TerrainShader.setUniform3f("dirLight.diffuse", glm::vec3(0.6f, 0.6f, 0.6f));
		m_TerrainShader.setUniform3f("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		m_TerrainShader.setUniform3f("spotLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		m_TerrainShader.setUniform3f("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		m_TerrainShader.setUniform3f("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		m_TerrainShader.setUniform1f("spotLight.constant", 1.0f);
		m_TerrainShader.setUniform1f("spotLight.linear", 0.0014);
		m_TerrainShader.setUniform1f("spotLight.quadratic", 0.000007);
		m_TerrainShader.setUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		m_TerrainShader.setUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		m_TerrainShader.setUniform3f("pointLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		m_TerrainShader.setUniform3f("pointLight.diffuse", glm::vec3(0.85f, 0.85f, 0.85f));
		m_TerrainShader.setUniform3f("pointLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		m_TerrainShader.setUniform1f("pointLight.constant", 1.0f);
		m_TerrainShader.setUniform1f("pointLight.linear", 0.007);
		m_TerrainShader.setUniform1f("pointLight.quadratic", 0.0002);

		// Model shader
		m_ModelShader.enable();
		m_ModelShader.setUniform1f("material.shininess", 128.0f);
		m_ModelShader.setUniform3f("dirLight.direction", glm::vec3(0.0f, -1.0f, 0.0f));
		m_ModelShader.setUniform3f("dirLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
		m_ModelShader.setUniform3f("dirLight.diffuse", glm::vec3(0.6f, 0.6f, 0.6f));
		m_ModelShader.setUniform3f("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		m_ModelShader.setUniform3f("spotLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		m_ModelShader.setUniform3f("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		m_ModelShader.setUniform3f("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		m_ModelShader.setUniform1f("spotLight.constant", 1.0f);
		m_ModelShader.setUniform1f("spotLight.linear", 0.0014);
		m_ModelShader.setUniform1f("spotLight.quadratic", 0.000007);
		m_ModelShader.setUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		m_ModelShader.setUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		m_ModelShader.setUniform3f("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		m_ModelShader.setUniform3f("pointLights[0].diffuse", glm::vec3(0.85f, 0.85f, 0.85f));
		m_ModelShader.setUniform3f("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		m_ModelShader.setUniform1f("pointLights[0].constant", 1.0f);
		m_ModelShader.setUniform1f("pointLights[0].linear", 0.007);
		m_ModelShader.setUniform1f("pointLights[0].quadratic", 0.0002);

		m_PlayerShader.enable();
		m_PlayerShader.setUniform1f("material.shininess", 128.0f);
		m_PlayerShader.setUniform3f("dirLight.direction", glm::vec3(0.0f, -1.0f, 0.0f));
		m_PlayerShader.setUniform3f("dirLight.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
		m_PlayerShader.setUniform3f("dirLight.diffuse", glm::vec3(0.6f, 0.6f, 0.6f));
		m_PlayerShader.setUniform3f("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		m_PlayerShader.setUniform3f("spotLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		m_PlayerShader.setUniform3f("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		m_PlayerShader.setUniform3f("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		m_PlayerShader.setUniform1f("spotLight.constant", 1.0f);
		m_PlayerShader.setUniform1f("spotLight.linear", 0.0014);
		m_PlayerShader.setUniform1f("spotLight.quadratic", 0.000007);
		m_PlayerShader.setUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		m_PlayerShader.setUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		m_PlayerShader.setUniform3f("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		m_PlayerShader.setUniform3f("pointLights[0].diffuse", glm::vec3(0.85f, 0.85f, 0.85f));
		m_PlayerShader.setUniform3f("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		m_PlayerShader.setUniform1f("pointLights[0].constant", 1.0f);
		m_PlayerShader.setUniform1f("pointLights[0].linear", 0.007);
		m_PlayerShader.setUniform1f("pointLights[0].quadratic", 0.0002);
	}

	void Scene3D::onUpdate(float deltaTime) {
		// Entity update
		auto iter = m_Entities.begin();
		while (iter != m_Entities.end()) {
			(*iter)->update(deltaTime);
			if ((*iter)->getShouldRemove()) {
				delete (*iter);
				m_Entities.erase(iter);
			}
			else {
				iter++;
			}
		}

		// Player update
		m_Player->update(deltaTime);

		// Check to see if the mouse hasn't been moved yet
		if (firstMove && (lastX != m_Window->getMouseX() || lastY != m_Window->getMouseY())) {
			lastX = m_Window->getMouseX();
			lastY = m_Window->getMouseY();
			firstMove = false;
		}

		// Camera Update
		m_Camera->processMouseMovement(m_Window->getMouseX() - lastX, lastY - m_Window->getMouseY(), m_Player);
		lastX = m_Window->getMouseX();
		lastY = m_Window->getMouseY();

		m_Camera->processMouseScroll(m_Window->getScrollY() * 6);
		m_Window->resetScroll();
		
		m_Camera->updateCamera(m_Player);
	}

	void Scene3D::onRender() {
		// Setup
		m_OutlineShader.enable();
		m_OutlineShader.setUniformMat4("view", m_Camera->getViewMatrix());
		m_OutlineShader.setUniformMat4("projection", glm::perspective(glm::radians(m_Camera->getFOV()), (float)m_Window->getWidth() / (float)m_Window->getHeight(), 0.1f, 3000.0f));

		// Models
		m_PlayerShader.enable();
		m_PlayerShader.setUniform3f("pointLights[0].position", glm::vec3(200.0f, 215.0f, 100.0f));
		m_PlayerShader.setUniform3f("spotLight.position", m_Player->getPosition() + (m_Player->getFront() * 15.0f));
		m_PlayerShader.setUniform3f("spotLight.direction", -m_Player->getUp() + m_Player->getFront());
		m_PlayerShader.setUniform3f("viewPos", m_Camera->getPosition());
		m_PlayerShader.setUniformMat4("view", m_Camera->getViewMatrix());
		m_PlayerShader.setUniformMat4("projection", glm::perspective(glm::radians(m_Camera->getFOV()), (float)m_Window->getWidth() / (float)m_Window->getHeight(), 0.1f, 3000.0f));

		// Models
		m_ModelShader.enable();
		m_ModelShader.setUniform3f("pointLights[0].position", glm::vec3(200.0f, 215.0f, 100.0f));
		m_ModelShader.setUniform3f("spotLight.position", m_Player->getPosition() + (m_Player->getFront() * 15.0f));
		m_ModelShader.setUniform3f("spotLight.direction", -m_Player->getUp() + m_Player->getFront());
		m_ModelShader.setUniform3f("viewPos", m_Camera->getPosition());
		m_ModelShader.setUniformMat4("view", m_Camera->getViewMatrix());
		m_ModelShader.setUniformMat4("projection", glm::perspective(glm::radians(m_Camera->getFOV()), (float)m_Window->getWidth() / (float)m_Window->getHeight(), 0.1f, 3000.0f));

		auto iter = m_Entities.begin();
		while (iter != m_Entities.end()) {
			graphics::Renderable3D *curr = (*iter)->getRenderable();
			if (curr->getTransparent()) {
				m_Renderer->submitTransparent(curr);
			}
			else {
				m_Renderer->submitOpaque(curr);
			}
			(*iter)->onRender();
			
			iter++;
		}

		auto renderableIter = m_Renderables.begin();
		while (renderableIter != m_Renderables.end()) {
			graphics::Renderable3D *curr = (*renderableIter);
			if (curr->getTransparent()) {
				m_Renderer->submitTransparent(curr);
			}
			else {
				m_Renderer->submitOpaque(curr);
			}

			renderableIter++;
		}

		// Terrain
		glStencilMask(0x00); // Don't update the stencil buffer
		glEnable(GL_CULL_FACE);
		m_TerrainShader.enable();
		m_TerrainShader.setUniform3f("pointLight.position", glm::vec3(200.0f, 200.0f, 100.0f));
		m_TerrainShader.setUniform3f("spotLight.position", m_Player->getPosition() + (m_Player->getFront() * 15.0f));
		m_TerrainShader.setUniform3f("spotLight.direction", -m_Player->getUp() + m_Player->getFront());
		m_TerrainShader.setUniform3f("viewPos", m_Camera->getPosition());
		glm::mat4 modelMatrix(1);
		modelMatrix = glm::translate(modelMatrix, m_Terrain->getPosition());
		m_TerrainShader.setUniformMat4("model", modelMatrix);
		m_TerrainShader.setUniformMat4("view", m_Camera->getViewMatrix());
		m_TerrainShader.setUniformMat4("projection", glm::perspective(glm::radians(m_Camera->getFOV()), (float)m_Window->getWidth() / (float)m_Window->getHeight(), 0.1f, 3000.0f));
		m_Terrain->Draw(m_TerrainShader);

		m_ModelShader.enable();
		m_Renderer->flushOpaque(m_ModelShader, m_OutlineShader);

		// Skybox
		m_Skybox->Draw();

		// Transparent objects
		m_ModelShader.enable();
		m_Renderer->flushTransparent(m_ModelShader, m_OutlineShader);


		// Player rendering (assumes the 4th texture unit is never used. This code will need refactoring but not enough time before demo)
		// Choose the shader depending if the camera is in 1st or 3rd person
		graphics::Shader *shaderToUse = &m_ModelShader;
		if (m_Camera->getThirdPerson()) {
			shaderToUse = &m_PlayerShader;
		}
		shaderToUse->enable();
		glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		glEnable(GL_BLEND); // Enable blending (note: You will still need to sort from back to front when rendering)
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); // Tell OpenGL how to blend, in this case make the new object have the transparency of its alpha and the object in the back is 1-alpha
		glm::mat4 model(1);
		glm::mat4 translate = glm::translate(glm::mat4(1.0f), m_Player->getRenderable()->getPosition());
		glm::mat4 rotate = glm::toMat4(m_Player->getRenderable()->getOrientation());
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), m_Player->getRenderable()->getScale());
		model = translate * rotate * scale;
		shaderToUse->setUniformMat4("model", model);
		if (m_Camera->getThirdPerson()) {
			glActiveTexture(GL_TEXTURE4);
			shaderToUse->setUniform1i("material.skyboxCubemap", 4);
			glBindTexture(GL_TEXTURE_CUBE_MAP, m_Skybox->getSkyboxCubemap());
		}
		m_Player->getRenderable()->draw(*shaderToUse);
	}

	void Scene3D::Add(game::Entity *entity) {
		m_Entities.push_back(entity);
	}

	void Scene3D::Add(graphics::Renderable3D *renderable) {
		m_Renderables.push_back(renderable);
	}

	void Scene3D::buttonPressed(unsigned int keycode, float deltaTime) {
		m_Player->buttonPressed(keycode, deltaTime);

		if (keycode == GLFW_KEY_C) {
			m_Camera->setThirdPerson(false);
		}
		if (keycode == GLFW_KEY_V) {
			m_Camera->setThirdPerson(true);
		}
	}

}
