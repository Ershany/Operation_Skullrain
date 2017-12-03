#pragma once

//Dependancies
#include "../Dependancies.h"

//STL Includes
#include <string>
#include <vector>

//Operation Skullrain Headers
#include "Primitive.h"


namespace arcane {
	namespace ui {
		struct Canvas {
			std::vector<ui::Primative*> primitives;
			Primative *health_bar;

			Canvas();
			void draw();
		};

	}
}