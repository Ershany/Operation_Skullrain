#include "Scene3D.h"

#include <iterator>
#include <iostream>
#include <string>
#include <glm/glm.hpp>

namespace arcane {

	Scene3D::Scene3D(graphics::Window *window)
		: m_TerrainShader("src/shaders/basic.vert", "src/shaders/terrain.frag"), m_ModelShader("src/shaders/basic.vert", "src/shaders/model.frag"), m_Window(window),
		m_OutlineShader("src/shaders/basic.vert", "src/shaders/basic.frag"), m_PlayerShader("src/shaders/player.vert", "src/shaders/player.frag", "src/shaders/player.geom"),
		m_ParticleShader("src/shaders/Particle.vert", "src/shaders/Particle.frag", "src/shaders/Particle.geom"),
		m_PlayerInvincibleShader("src/shaders/player.vert", "src/shaders/playerInvincible.frag", "src/shaders/player.geom")
	{
		m_Camera = new graphics::Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
		m_Renderer = new graphics::Renderer(m_Camera);
		m_Terrain = new terrain::Terrain(glm::vec3(-1280.0f, -20.0f, -1280.0f)); // Make it so the center of the terrain is on the origin

		std::cout << "Loading Projectiles" << std::endl;
		m_CannonBall = new arcane::graphics::Model("res/3D_Models/Cannon/cannon.obj");

		std::cout << "Loading Player Models" << std::endl;
		//Low poly heli
		//graphics::Renderable3D *player_helicopter_body = new graphics::Renderable3D(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(4.0f, 4.0f, 4.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(0.0f), new arcane::graphics::Model("res/3D_Models/Helicopter/body_low_poly.obj"), nullptr, false);

		//Regular poly heli (loads slower)
		graphics::Renderable3D *player_helicopter_body = new graphics::Renderable3D(glm::vec3(90.0f, -10.0f, 90.0f), glm::vec3(4.0f, 4.0f, 4.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(0.0f), new arcane::graphics::Model("res/3D_Models/Helicopter/body.obj"), nullptr, false, true);
		m_Player = new game::Player(player_helicopter_body,
			new graphics::Renderable3D(glm::vec3(0.0f, 6.5f, 0.0f), glm::vec3(4.0f, 4.0f, 4.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(0.0f), new arcane::graphics::Model("res/3D_Models/Helicopter/main_rotor.obj"), player_helicopter_body, false, false),
			new graphics::Renderable3D(glm::vec3(0.0f, 9.8f, 42.0f), glm::vec3(4.0f, 4.0f, 4.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::radians(0.0f), new arcane::graphics::Model("res/3D_Models/Helicopter/back_rotor.obj"), player_helicopter_body, false, false), m_Terrain, m_firing);

		std::cout << "Preparing Scene" << std::endl;
		m_VegSpawner = new terrain::VegetationSpawner(m_Terrain, 500);
		m_PlayerDeathExplosion = graphics::ParticleFactory::CreateExplosion(opengl::Utility::loadTextureFromFile("res/textures/fire.png", true), 100000, 0.25f, m_Player->getPosition() + glm::vec3(0.0f, 10.0f, 0.0f), false);
		m_TowerSpawner = new game::TowerSpawner(m_Terrain, 5, m_CannonBall, m_Player, &m_Entities);
		m_UI = new ui::Canvas(m_Window, m_Player);
		m_ParticleRenderer = new graphics::ParticleRenderer(window, m_Camera, m_Player);
		std::cout << "Loading NPCs" << std::endl;
		m_NPCSpawner = new game::NPCSpawner(m_Terrain, 20, m_Player);
		std::cout << "Finished Loading" << std::endl;

		firstMove = true;
		lastX = m_Window->getMouseX();
		lastY = m_Window->getMouseY();

		m_PlayerRemoved = false;
		*m_firing = false;

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
		delete m_UI;
		delete m_TowerSpawner;
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

		auto towerIter = m_TowerSpawner->getBegin();
		while (towerIter != m_TowerSpawner->getEnd()) {
			Add(*towerIter);
			towerIter++;
		}

		// Terrain shader
		m_TerrainShader.enable();
		m_TerrainShader.setUniform1f("material.shininess", 128.0f);
		m_TerrainShader.setUniform3f("dirLight.direction", glm::vec3(0.0f, -1.0f, 0.0f));
		m_TerrainShader.setUniform3f("dirLight.ambient", glm::vec3(0.2f, 0.15f, 0.15f));
		m_TerrainShader.setUniform3f("dirLight.diffuse", glm::vec3(0.45f, 0.35f, 0.35f));
		m_TerrainShader.setUniform3f("dirLight.specular", glm::vec3(0.1f, 0.1f, 0.1f));
		m_TerrainShader.setUniform3f("spotLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		m_TerrainShader.setUniform3f("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		m_TerrainShader.setUniform3f("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		m_TerrainShader.setUniform1f("spotLight.constant", 1.0f);
		m_TerrainShader.setUniform1f("spotLight.linear", 0.0014);
		m_TerrainShader.setUniform1f("spotLight.quadratic", 0.000007);
		m_TerrainShader.setUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		m_TerrainShader.setUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		m_TerrainShader.setUniform3f("pointLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		m_TerrainShader.setUniform3f("pointLight.diffuse", glm::vec3(0.95f, 0.95f, 0.95f));
		m_TerrainShader.setUniform3f("pointLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		m_TerrainShader.setUniform1f("pointLight.constant", 1.0f);
		m_TerrainShader.setUniform1f("pointLight.linear", 0.007);
		m_TerrainShader.setUniform1f("pointLight.quadratic", 0.0002);

		// Model shader
		m_ModelShader.enable();
		m_ModelShader.setUniform1f("material.shininess", 128.0f);
		m_ModelShader.setUniform3f("dirLight.direction", glm::vec3(0.0f, -1.0f, 0.0f));
		m_ModelShader.setUniform3f("dirLight.ambient", glm::vec3(0.2f, 0.15f, 0.15f));
		m_ModelShader.setUniform3f("dirLight.diffuse", glm::vec3(0.45f, 0.35f, 0.35f));
		m_ModelShader.setUniform3f("dirLight.specular", glm::vec3(0.1f, 0.1f, 0.1f));
		m_ModelShader.setUniform3f("spotLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		m_ModelShader.setUniform3f("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		m_ModelShader.setUniform3f("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		m_ModelShader.setUniform1f("spotLight.constant", 1.0f);
		m_ModelShader.setUniform1f("spotLight.linear", 0.0014);
		m_ModelShader.setUniform1f("spotLight.quadratic", 0.000007);
		m_ModelShader.setUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		m_ModelShader.setUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		m_ModelShader.setUniform3f("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		m_ModelShader.setUniform3f("pointLights[0].diffuse", glm::vec3(0.6f, 0.1f, 0.1f));
		m_ModelShader.setUniform3f("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		m_ModelShader.setUniform1f("pointLights[0].constant", 1.0f);
		m_ModelShader.setUniform1f("pointLights[0].linear", 0.007);
		m_ModelShader.setUniform1f("pointLights[0].quadratic", 0.0002);

		m_PlayerShader.enable();
		m_PlayerShader.setUniform1f("material.shininess", 128.0f);
		m_PlayerShader.setUniform3f("dirLight.direction", glm::vec3(0.0f, -1.0f, 0.0f));
		m_PlayerShader.setUniform3f("dirLight.ambient", glm::vec3(0.2f, 0.15f, 0.15f));
		m_PlayerShader.setUniform3f("dirLight.diffuse", glm::vec3(0.45f, 0.35f, 0.35f));
		m_PlayerShader.setUniform3f("dirLight.specular", glm::vec3(0.1f, 0.1f, 0.1f));
		m_PlayerShader.setUniform3f("spotLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		m_PlayerShader.setUniform3f("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		m_PlayerShader.setUniform3f("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		m_PlayerShader.setUniform1f("spotLight.constant", 1.0f);
		m_PlayerShader.setUniform1f("spotLight.linear", 0.0014);
		m_PlayerShader.setUniform1f("spotLight.quadratic", 0.000007);
		m_PlayerShader.setUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		m_PlayerShader.setUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		m_PlayerShader.setUniform3f("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		m_PlayerShader.setUniform3f("pointLights[0].diffuse", glm::vec3(0.6f, 0.1f, 0.1f));
		m_PlayerShader.setUniform3f("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		m_PlayerShader.setUniform1f("pointLights[0].constant", 1.0f);
		m_PlayerShader.setUniform1f("pointLights[0].linear", 0.007);
		m_PlayerShader.setUniform1f("pointLights[0].quadratic", 0.0002);

		m_PlayerInvincibleShader.enable();
		m_PlayerInvincibleShader.setUniform1f("material.shininess", 128.0f);
		m_PlayerInvincibleShader.setUniform3f("dirLight.direction", glm::vec3(0.0f, -1.0f, 0.0f));
		m_PlayerInvincibleShader.setUniform3f("dirLight.ambient", glm::vec3(0.2f, 0.15f, 0.15f));
		m_PlayerInvincibleShader.setUniform3f("dirLight.diffuse", glm::vec3(0.45f, 0.35f, 0.35f));
		m_PlayerInvincibleShader.setUniform3f("dirLight.specular", glm::vec3(0.1f, 0.1f, 0.1f));
		m_PlayerInvincibleShader.setUniform3f("spotLight.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		m_PlayerInvincibleShader.setUniform3f("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
		m_PlayerInvincibleShader.setUniform3f("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		m_PlayerInvincibleShader.setUniform1f("spotLight.constant", 1.0f);
		m_PlayerInvincibleShader.setUniform1f("spotLight.linear", 0.0014);
		m_PlayerInvincibleShader.setUniform1f("spotLight.quadratic", 0.000007);
		m_PlayerInvincibleShader.setUniform1f("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		m_PlayerInvincibleShader.setUniform1f("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
		m_PlayerInvincibleShader.setUniform3f("pointLights[0].ambient", glm::vec3(0.05f, 0.05f, 0.05f));
		m_PlayerInvincibleShader.setUniform3f("pointLights[0].diffuse", glm::vec3(0.6f, 0.1f, 0.1f));
		m_PlayerInvincibleShader.setUniform3f("pointLights[0].specular", glm::vec3(1.0f, 1.0f, 1.0f));
		m_PlayerInvincibleShader.setUniform1f("pointLights[0].constant", 1.0f);
		m_PlayerInvincibleShader.setUniform1f("pointLights[0].linear", 0.007);
		m_PlayerInvincibleShader.setUniform1f("pointLights[0].quadratic", 0.0002);

		// Initialize particles
		m_ParticleRenderer->addParticle(m_PlayerDeathExplosion);
	}

	void Scene3D::onUpdate(float deltaTime) {
		//Only let them fire again if it has been 5 seconds since the last time
		if (*m_firing && glfwGetTime() - m_lastFireStart > 5.0f) {
			m_lastFireStart = glfwGetTime();
		}
		//If it is greater than 3 seconds, reset m_firing
		else if (*m_firing && glfwGetTime() - m_lastFireStart > 3.0f) {
			*m_firing = false;
		}

		//Fire for the first 3 seconds
		if (*m_firing && glfwGetTime() - m_lastFireStart < 2.0f) {
			if (glfwGetTime() - m_lastBulletTime > m_fireRate) {
				//std::cout << "Shooting" << std::endl;
				int borderBoundary = 2;

				glm::vec3 pos = m_Player->getPosition() + m_Player->getFront() * 20.0f;
				//pos += repositionVec;
				game::Cannon *new_projectile = new game::Cannon(m_Terrain, new graphics::Renderable3D(pos, glm::vec3(0.2f, 0.2f, 0.2f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0f, m_CannonBall, nullptr), m_Player);

				new_projectile->m_DirectionToMove = glm::normalize(m_Player->getFront()) * glm::vec3(5.0f, 5.0f, 5.0f);// *1.0f;
				//std::cout << new_projectile->m_DirectionToMove.x << ", " << new_projectile->m_DirectionToMove.y << ", " << new_projectile->m_DirectionToMove.z << std::endl;
				new_projectile->m_LifeLength = 0.5f;
				m_Entities.push_back(new_projectile);
			}
		}

		//// Entity update
		//auto iter = m_Entities.begin();
		//while (iter != m_Entities.end()) {
		//	(*iter)->update(deltaTime);
		//	if ((*iter)->getShouldRemove()) {
		//		m_Entities.erase(iter);
		//		delete (*iter);
		//	}
		//	else {
		//		iter++;
		//	}
		//}
		//float time = glfwGetTime() * 2;
		std::cout << glfwGetTime() << std::endl;

		for (int i = 0; i < m_Entities.size(); i++) {
			arcane::game::Entity* this_entity = m_Entities.at(i);
			this_entity->update(deltaTime);
			if (this_entity->getShouldRemove()) {
				m_Entities.erase(m_Entities.begin() + i);
				delete (this_entity);
			}
		}

		// Player update
		m_Player->update(deltaTime);
		if (m_Player->isDead() && !m_PlayerRemoved) {
			Remove(m_Player->getMainRotor());
			Remove(m_Player->getBackRotor());
			m_DeathAnimTime.reset();
			m_PlayerRemoved = true;
			m_PlayerDeathExplosion->setActive(true);
			m_PlayerDeathExplosion->setPosition(m_Player->getPosition());
		}

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
		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		//UI
		m_UI->draw();

		glm::vec3 spotLightPos = m_Player->getPosition() + (m_Player->getFront() * 15.0f);
		glm::vec3 spotLightDir = -m_Player->getUp() + m_Player->getFront();
		glm::vec3 pointLightPos = m_Player->getPosition();
		glm::mat4 viewMtrx = m_Camera->getViewMatrix();
		glm::mat4 projectionMtrx = glm::perspective(glm::radians(m_Camera->getFOV()), (float)m_Window->getWidth() / (float)m_Window->getHeight(), 0.1f, 3000.0f);
		if (m_Player->isDead()) { // Hide the spotlight when the player dies
			spotLightPos = glm::vec3(0.0f, 10000.0f, 0.0f);
			pointLightPos = glm::vec3(0.0f, 10000.0f, 0.0f);
		}

		// Setup
		m_OutlineShader.enable();
		m_OutlineShader.setUniformMat4("view", viewMtrx);
		m_OutlineShader.setUniformMat4("projection", projectionMtrx);

		// Models
		m_PlayerShader.enable();
		m_PlayerShader.setUniform3f("pointLights[0].position", pointLightPos);
		m_PlayerShader.setUniform3f("spotLight.position", spotLightPos);
		m_PlayerShader.setUniform3f("spotLight.direction", spotLightDir);
		m_PlayerShader.setUniform3f("viewPos", m_Camera->getPosition());
		m_PlayerShader.setUniformMat4("view", viewMtrx);
		m_PlayerShader.setUniformMat4("projection", projectionMtrx);

		m_PlayerInvincibleShader.enable();
		m_PlayerInvincibleShader.setUniform3f("pointLights[0].position", pointLightPos);
		m_PlayerInvincibleShader.setUniform3f("spotLight.position", spotLightPos);
		m_PlayerInvincibleShader.setUniform3f("spotLight.direction", spotLightDir);
		m_PlayerInvincibleShader.setUniform3f("viewPos", m_Camera->getPosition());
		m_PlayerInvincibleShader.setUniformMat4("view", viewMtrx);
		m_PlayerInvincibleShader.setUniformMat4("projection", projectionMtrx);

		// Models
		m_ModelShader.enable();
		m_ModelShader.setUniform3f("pointLights[0].position", pointLightPos);
		m_ModelShader.setUniform3f("spotLight.position", spotLightPos);
		m_ModelShader.setUniform3f("spotLight.direction", spotLightDir);
		m_ModelShader.setUniform3f("viewPos", m_Camera->getPosition());
		m_ModelShader.setUniformMat4("view", viewMtrx);
		m_ModelShader.setUniformMat4("projection", projectionMtrx);

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
		m_TerrainShader.setUniform3f("pointLight.position", pointLightPos);
		m_TerrainShader.setUniform3f("spotLight.position", spotLightPos);
		m_TerrainShader.setUniform3f("spotLight.direction", spotLightDir);
		m_TerrainShader.setUniform3f("viewPos", m_Camera->getPosition());
		glm::mat4 modelMatrix(1);
		modelMatrix = glm::translate(modelMatrix, m_Terrain->getPosition());
		m_TerrainShader.setUniformMat4("model", modelMatrix);
		m_TerrainShader.setUniformMat4("view", viewMtrx);
		m_TerrainShader.setUniformMat4("projection", projectionMtrx);
		m_Terrain->Draw(m_TerrainShader);

		m_ModelShader.enable();
		m_Renderer->flushOpaque(m_ModelShader, m_OutlineShader);

		// Skybox
		m_Skybox->Draw();

		// Transparent objects
		m_ModelShader.enable();
		m_Renderer->flushTransparent(m_ModelShader, m_OutlineShader);

		// Render particles
		m_ParticleShader.enable();
		m_ParticleRenderer->render(m_ParticleShader);

		// Player rendering (assumes the 4th texture unit is never used. This code will need refactoring but not enough time before demo)
		// Choose the shader depending if the camera is in 1st or 3rd person
		graphics::Shader *shaderToUse = &m_ModelShader;
		if (m_Camera->getThirdPerson()) {
			if (m_Player->isInvincible()) {
				shaderToUse = &m_PlayerInvincibleShader;
			}
			else {
				shaderToUse = &m_PlayerShader;
			}
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
			float animTimer = 0.0f;
			if (m_Player->isDead()) {
				animTimer = m_DeathAnimTime.elapsed();
			}
			shaderToUse->setUniform1f("timer", animTimer);
		}
		m_Player->getRenderable()->draw(*shaderToUse);
	}

	void Scene3D::Add(game::Entity *entity) {
		m_Entities.push_back(entity);
	}

	void Scene3D::Add(graphics::Renderable3D *renderable) {
		m_Renderables.push_back(renderable);
	}

	void Scene3D::Remove(game::Entity *entity) {
		auto iter = m_Entities.begin();
		while (iter != m_Entities.end()) {
			if ((*iter) == entity) {
				m_Entities.erase(iter);
				break;
			}
			iter++;
		}
	}

	void Scene3D::Remove(graphics::Renderable3D *renderable) {
		auto iter = m_Renderables.begin();
		while (iter != m_Renderables.end()) {
			if ((*iter) == renderable) {
				m_Renderables.erase(iter);
				break;
			}
			iter++;
		}
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