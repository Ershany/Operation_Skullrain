#pragma once

//Dependancies
#include "../../Dependancies.h"

//STL Includes
#include <vector>

//Operation Skullrain Headers
#include "../camera/Camera.h"
#include "../Particle.h"
#include "../ParticleFactory.h"
#include "../../platform/OpenGL/Utility.h"
#include "../Window.h"

namespace arcane { namespace graphics {

	class ParticleRenderer {
	public:
		ParticleRenderer(graphics::Window *window, Camera *camera, game::Player *player);

		void update(float deltaTime);
		void render(graphics::Shader &shader);
	private:
		graphics::Window *m_Window;
		Camera *m_Camera;
		
		std::vector<Particle*> m_ParticleQueue;
	};

} }