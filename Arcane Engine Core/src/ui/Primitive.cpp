#include "Primitive.h"
#include <sstream>

namespace arcane {
	namespace ui {
		Rect::Rect(int x, int y, int width, int height) {
			this->x = y; this->y = y; this->width = width; this->height = height;
		}

		HealthBar::HealthBar(int max_health, int x, int y, int width, int height) {
			this->max_health = max_health;
			this->curr_health = max_health;

			this->x = y; this->y = y; this->width = width; this->height = height;
		}
	};

}