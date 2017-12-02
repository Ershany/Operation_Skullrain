#pragma once

#include <glm/glm.hpp>
#include <assimp\Importer.hpp>
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
		};

		struct HealthBar : public Rect {
			float max_health, curr_health;

			HealthBar();
			HealthBar(int max_health, int x, int y, int width, int height);
		};

	}
}