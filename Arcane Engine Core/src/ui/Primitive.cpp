#include "Primitive.h"
#include <sstream>
#include <glm/glm.hpp>
#include <iostream>

namespace arcane { namespace ui {

	Primitive::Primitive(graphics::Window *window, GLuint texture) : m_TextureID(texture) {
		m_Window = window;
	}

	Primitive::~Primitive() {
	}

	void Primitive::draw(graphics::Shader &shader) {
	}

	Rect::Rect(graphics::Window *window, GLuint texture, GLfloat x, GLfloat y, GLfloat width, GLfloat height) : Primitive(window, texture) {
		this->x = y; this->y = y; this->width = width; this->height = height;

		//GLfloat positions[] = {
		//	-xPos,			  yPos + uiHeight,  0.0f,
		//	 xPos + uiWidth,  yPos + uiHeight,  0.0f,
		//	-xPos,			 -yPos,				0.0f,
		//	 xPos + uiWidth, -yPos,				0.0f
		//};
		GLfloat positions[] = {
			x, y, 0.0f,
			x + width, y, 0.0f,
			x, y - height, 0.0f,
			x + width, y - height, 0.0f
		};
		GLfloat uvs[] = {
			0.0f, 0.0f,
			1.0f, 0.0f,
			0.0f, 1.0f,
			1.0f, 1.0f
		};
		GLuint indices[] = { 2, 1, 0, 2, 3, 1 };
		m_Ebo.load(indices, 6);
		m_Vao.addBuffer(new opengl::Buffer(positions, 3 * 4, 3), 0);
		m_Vao.addBuffer(new opengl::Buffer(uvs, 2 * 4, 2), 1);
	}

	void Rect::draw(graphics::Shader &shader) {
		//This UI folder is meant to allow calls to be made so that any simple shapes can be made and rendered.
		//The Canvas is the layer that has all of the shapes on it. I'll look into adding text later.

		//The program gets to here just fine. How should the rendering be done?
		//If you can get it to display a rectangle, I can take care of the rest of the
		//healthbar implementation. :)

		glActiveTexture(GL_TEXTURE0);
		shader.setUniform1i("uiTexture", 0);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		m_Vao.bind();
		m_Ebo.bind();
		glDrawElements(GL_TRIANGLES, m_Ebo.getCount(), GL_UNSIGNED_INT, 0);
		m_Ebo.unbind();
		m_Vao.unbind();
	}

	//HealthBar::HealthBar(GLuint texture, int max_health, int x, int y, int width, int height) : Rect(texture) {
	//	this->max_health = max_health;
	//	this->curr_health = max_health;
	//
	//	this->x = y; this->y = y; this->width = width; this->height = height;
	//}

} }