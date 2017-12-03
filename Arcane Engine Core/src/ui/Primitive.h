#pragma once

//Dependancies
#include "../Dependancies.h"

//STL Includes
#include <string>
#include <vector>

namespace arcane {
	namespace ui {
		struct Primative {

		};

		struct Rect: public Primative {
			int x, y, width, height;

			Rect();
			Rect(int x, int y, int width, int height);

			void draw();
		};

		struct HealthBar : public Rect {
			float max_health, curr_health;

			HealthBar();
			HealthBar(int max_health, int x, int y, int width, int height);
		};

	}
}