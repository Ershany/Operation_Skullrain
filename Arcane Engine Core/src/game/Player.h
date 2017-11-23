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
		inline glm::vec3 getFront() { return m_Orientation * m_InitialFront; }
		inline glm::vec3 getUp() { return m_Orientation * m_InitialUp; }
		inline glm::vec3 getRight() { return m_Orientation * glm::cross(m_InitialFront, m_InitialUp); }
	private:
		glm::quat m_Orientation;
		glm::vec3 m_Velocity;
		glm::vec3 m_InitialFront, m_InitialUp;
	};

} }