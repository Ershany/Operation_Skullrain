#pragma once

#include "Entity.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>

namespace arcane { namespace game {

	class Player : public Entity {
	public:
		Player(graphics::Renderable3D *renderable);
		~Player();

		virtual void update(double deltaTime) override;

		void buttonPressed(unsigned int keycode);
	private:
		glm::vec3 m_Velocity, m_Front, m_Up;
	};

} }