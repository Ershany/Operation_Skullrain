#pragma once

#include <glm/glm.hpp>
#include <assimp\Importer.hpp>
#include <string>
#include <vector>
#include "Primitive.h"

namespace arcane {
	namespace ui {
		struct Canvas {
			std::vector<ui::Primative> primitives;
			Primative *health_bar;

			Canvas();
		};

	}
}