#pragma once

//Dependancies
#include "../../Dependancies.h"

//STL Includes
#include <deque>

//Operation Skullrain Headers
#include "../Model.h"
#include "../camera/Camera.h"
#include "Renderable3D.h"

namespace arcane { namespace graphics {
	class Renderer {
	public:
		Renderer(Camera *camera);

		void submitOpaque(Renderable3D *renderable);
		void submitTransparent(Renderable3D *renderable);
		
		void flushOpaque(Shader &shader, Shader &outlineShader);
		void flushTransparent(Shader &shader, Shader &outlineShader);
	private:
		std::deque<Renderable3D*> m_OpaqueRenderQueue;
		std::deque<Renderable3D*> m_TransparentRenderQueue;

		Camera *m_Camera;
	};
} }