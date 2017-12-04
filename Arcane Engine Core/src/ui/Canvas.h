#pragma once

//Dependancies
#include "../Dependancies.h"

//STL Includes
#include <string>
#include <vector>

//Operation Skullrain Headers
#include "Primitive.h"
#include "../graphics/Window.h"
#include "../graphics/Shader.h"
#include "../platform/OpenGL/Utility.h"


namespace arcane { namespace ui {
		
	class Canvas {
	public:
		Canvas(graphics::Window *window);
		void draw();
	private:
		std::vector<ui::Primitive*> primitives;
		Primitive *health_bar;

		graphics::Shader m_UIShader;
		graphics::Window *m_Window;
	};

} }