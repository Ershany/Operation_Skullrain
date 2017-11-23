#include "Camera.h"

#include <iostream>

namespace arcane {	namespace graphics {

	Camera::Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH)
		: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_FOV(FOV)
	{
		m_Position = position;
		m_WorldUp = up;
		m_Up = up;
		m_Yaw = yaw;
		m_Pitch = pitch;
		m_ThirdPerson = true;
		updateCameraVectors();
	}

	Camera::Camera(GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat xUp, GLfloat yUp, GLfloat zUp, GLfloat yaw = YAW, GLfloat pitch = PITCH)
		: m_Front(glm::vec3(0.0f, 0.0f, -1.0f)), m_MovementSpeed(SPEED), m_MouseSensitivity(SENSITIVITY), m_FOV(FOV)
	{
		m_Position = glm::vec3(xPos, yPos, zPos);
		m_WorldUp = glm::vec3(xUp, yUp, zUp);
		m_Yaw = yaw;
		m_Pitch = pitch;
		m_ThirdPerson = true;
		updateCameraVectors();
	}

	void Camera::updateCamera(game::Player *player) {
		if (m_ThirdPerson) {
			m_Pitch = 0.0f;
			m_Position = player->getPosition() - (player->getFront() * 54.0f) + (m_WorldUp * 34.0f);
			m_Position = (glm::toMat3(glm::angleAxis(glm::radians(-m_Yaw), player->getUp())) * (m_Position - player->getPosition())) + player->getPosition(); // orbit the camera around the player
			m_Front = glm::normalize(player->getPosition() - m_Position);
		}
		else {
			m_Position = player->getPosition() + (player->getFront() * 11.6f) + (m_WorldUp * 2.7f) - (player->getRight() * 2.7f);
		}
	}

	glm::mat4 Camera::getViewMatrix() {
		return glm::lookAt(m_Position, m_Position + m_Front, m_Up);
	}

	void Camera::processMouseMovement(GLfloat xOffset, GLfloat yOffset, game::Player *player) {
		xOffset *= m_MouseSensitivity;
		yOffset *= m_MouseSensitivity;

		m_Yaw += xOffset;

		if(!m_ThirdPerson)
			m_Pitch += yOffset;

		// Constrain the pitch
		if (m_Pitch > 45.0f) {
			m_Pitch = 45.0f;
		}
		else if (m_Pitch < -45.0f) {
			m_Pitch = -45.0f;
		}

		updateCameraVectors();
	}

	void Camera::processMouseScroll(GLfloat offset) {
		if (offset != 0 && m_FOV >= 1.0f && m_FOV <= FOV) {
			m_FOV -= offset;
		}
		if (m_FOV < 1.0f) {
			m_FOV = 1.0f;
		}
		else if (m_FOV > FOV) {
			m_FOV = FOV;
		}
	}

	void Camera::updateCameraVectors() {
		glm::vec3 front;
		front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		front.y = sin(glm::radians(m_Pitch));
		front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		m_Front = glm::normalize(front);

		// Recalculate Vectors
		m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
		m_Up = glm::normalize(glm::cross(m_Right, m_Front));
	}

} }