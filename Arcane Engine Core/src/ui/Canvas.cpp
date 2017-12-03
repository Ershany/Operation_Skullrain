#include "Canvas.h"
#include <sstream>
#include <iostream>

namespace arcane {
	namespace ui {
		Canvas::Canvas() {
			health_bar = new ui::HealthBar();

			primitives.push_back(health_bar);
		}

		void Canvas::draw() {
			std::vector<ui::Primative*>::iterator itr;
			for (int i = 0; i < primitives.size(); i++) {
				primitives.at(i)->draw();
			}
		}
	};

}