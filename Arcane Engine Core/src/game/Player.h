#pragma once

#include "Entity.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace arcane { namespace game {

	class Player : public Entity {
	public:
		Player(graphics::Renderable3D *renderable);
		~Player();

		virtual void update(float deltaTime) override;

		void buttonPressed(unsigned int keycode, float deltaTime);

		// Getters
		inline glm::vec3 getFront() { return m_Front; }
		inline glm::vec3 getUp() { return m_Up; }
		inline glm::vec3 getRight() { return glm::cross(m_Front, m_Up); }
	private:
		glm::quat m_Orientation;
		glm::vec3 m_Velocity;
		glm::vec3 m_Front, m_Up;
		glm::vec3 m_InitialFront, m_InitialUp;
	};

} }