#pragma once

#include "Entity.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\gtx\norm.hpp>

namespace arcane { namespace game {

	class Player : public Entity {
	public:
		Player(graphics::Renderable3D *renderable);
		~Player();

		virtual void update(float deltaTime) override;

		void buttonPressed(unsigned int keycode, float deltaTime);

		// Getters
		inline const glm::vec3& getFront() { return m_Orientation * m_InitialFront; }
		inline const glm::vec3& getUp() { return m_Orientation * m_InitialUp; }
		inline const glm::vec3& getRight() { return glm::normalize(glm::cross(getFront(), getUp())); }
		inline const glm::quat& getOrientation() { return m_Orientation; }
	private:
		glm::quat m_Orientation;

		glm::vec3 m_Velocity;
		GLfloat m_TerminalVelocity, m_TerminalVelocitySquared;

		glm::vec3 m_InitialFront, m_InitialUp;
	};

} }