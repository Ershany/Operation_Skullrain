#pragma once

//Dependancies
#include "../Dependancies.h"

//STL Includes
#include <string>
#include <vector>

//Game Includes
#include "../graphics/Shader.h"
#include "../graphics/Window.h"
#include "../platform/OpenGL/VertexArray.h"
#include "../platform/OpenGL/IndexBuffer.h"

namespace arcane { namespace ui {

	struct Primitive {
		Primitive(graphics::Window *window, GLuint texture);
		virtual ~Primitive();

		virtual void draw(graphics::Shader &shader) = 0;
	protected:
		opengl::VertexArray m_Vao;
		opengl::IndexBuffer m_Ebo;

		GLuint m_TextureID;
		graphics::Window *m_Window;
	};

	struct Rect: public Primitive {
		Rect(graphics::Window *window, GLuint texture, GLfloat x, GLfloat y, GLfloat width, GLfloat height);

		virtual void draw(graphics::Shader &shader) override;

		GLfloat x, y, width, height; // Should all be in screen coordinates [-1, 1], and X and Y represents the top left of the UI
	};

	//struct HealthBar : public Rect {
	//	float max_health, curr_health;
	//
	//	HealthBar(graphics::Window *window, GLuint texture, int max_health, GLfloat x, GLfloat y, GLfloat width, GLfloat height);
	//};

} }