#include "Canvas.h"
#include <sstream>

namespace arcane {
	namespace ui {
		Canvas::Canvas() {
			health_bar = new ui::HealthBar();
		}
	};

}