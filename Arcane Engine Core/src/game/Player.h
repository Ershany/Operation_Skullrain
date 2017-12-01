#pragma once

#include "Entity.h"
#include "../terrain/Terrain.h"

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\gtx\norm.hpp>

namespace arcane { namespace game {

	class Player : public Entity {
	public:
		Player(graphics::Renderable3D *renderable, graphics::Renderable3D *main_rotor, graphics::Renderable3D *back_rotor, terrain::Terrain *terrain);
		~Player();

		virtual void update(float deltaTime) override;
		virtual void onRender();

		void pickupNPC();

		void buttonPressed(unsigned int keycode, float deltaTime);

		// Getters
		inline const glm::vec3& getFront() { return m_Orientation * m_InitialFront; }
		inline const glm::vec3& getUp() { return m_Orientation * m_InitialUp; }
		inline const glm::vec3& getRight() { return glm::normalize(glm::cross(getFront(), getUp())); }
		inline const glm::quat& getOrientation() { return m_Orientation; }
		inline const glm::vec3& getVelocity() { return m_Velocity; }
		inline bool isGrounded() { return m_IsGrounded; }
		inline bool isDead() { return m_IsDead; }

		inline graphics::Renderable3D* getMainRotor() { return m_MainRotor; }
		inline graphics::Renderable3D* getBackRotor() { return m_BackRotor; }
	private:
		glm::quat m_Orientation;

		glm::vec3 m_Velocity;
		glm::vec3 m_Lift;

		const float m_MaxRotorRotationAmount;
		const float m_MinRotorRotationAmount;
		float m_CurrentRotorRotationAmount;

		float m_Tilt, m_TiltAmount;
		float m_MainTilt, m_SideTilt;

		GLfloat m_TerminalVelocity, m_TerminalVelocitySquared;

		glm::vec3 m_InitialFront, m_InitialUp;

		terrain::Terrain *m_Terrain;
		bool m_IsGrounded, m_IsDead;
		int m_NPCPickupCount;

		graphics::Renderable3D *m_MainRotor, *m_BackRotor;
	};

} }