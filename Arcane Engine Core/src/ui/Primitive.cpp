#include "Primitive.h"
#include <sstream>
#include <glm/glm.hpp>
#include <iostream>

namespace arcane {
	namespace ui {
		Primative::Primative() {
		}

		void Primative::draw() {
		}

		Rect::Rect() {
		}

		Rect::Rect(int x, int y, int width, int height) {
			this->x = y; this->y = y; this->width = width; this->height = height;
		}

		void Rect::draw() {
			//This UI folder is meant to allow calls to be made so that any simple shapes can be made and rendered.
			//The Canvas is the layer that has all of the shapes on it. I'll look into adding text later.

			//The program gets to here just fine. How should the rendering be done?
			//If you can get it to display a rectangle, I can take care of the rest of the
			//healthbar implementation. :)

			std::cout << "Made it to rect" << std::endl;
			// Draw a Red 1x1 Square centered at origin
			glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
			glColor3f(1.0f, 0.0f, 0.0f); // Red
			glVertex2f(-0.5f, -0.5f);    // x, y
			glVertex2f(0.5f, -0.5f);
			glVertex2f(0.5f, 0.5f);
			glVertex2f(-0.5f, 0.5f);
			glEnd();

			glFlush();  // Render now
		}

		HealthBar::HealthBar() {
		}

		HealthBar::HealthBar(int max_health, int x, int y, int width, int height) {
			this->max_health = max_health;
			this->curr_health = max_health;

			this->x = y; this->y = y; this->width = width; this->height = height;
		}
	};

}