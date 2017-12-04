#include "Canvas.h"
#include <sstream>
#include <iostream>

namespace arcane { namespace ui {

	Canvas::Canvas(graphics::Window *window) : m_UIShader("src/shaders/UI.vert", "src/shaders/UI.frag") {
		m_Window = window;

		health_bar = new ui::Rect(window, opengl::Utility::loadTextureFromFile("res/textures/healthbar.png"), -1.0f, 1.0f, 1.0f, 0.2f); // Top left
		primitives.push_back(health_bar);
	}

	void Canvas::draw() {
		m_UIShader.enable();

		std::vector<ui::Primitive*>::iterator itr;
		for (int i = 0; i < primitives.size(); i++) {
			primitives.at(i)->draw(m_UIShader);
		}
	}

} }