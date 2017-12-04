#pragma once

//Dependancies
#include "../Dependancies.h"

//STL Includes
#include <string>
#include <vector>

//Operation Skullrain Headers
#include "Primitive.h"
#include "../game/Player.h"
#include "../graphics/Window.h"
#include "../graphics/Shader.h"
#include "../platform/OpenGL/Utility.h"


namespace arcane { namespace ui {
		
	class Canvas {
	public:
		Canvas(graphics::Window *window, game::Player *player);
		void draw();
	private:
		std::vector<ui::Primitive*> m_Primitives;
		Primitive *m_HealthBar;

		graphics::Shader m_UIShader;
		graphics::Window *m_Window;
		game::Player *m_Player;
	};

} }