#pragma once

//Dependancies
#include "../Dependancies.h"

//STL Includes
#include <vector>

//Operation Skullrain Headers
#include "Mesh.h"
#include "../platform/OpenGL/Utility.h"

namespace arcane { namespace graphics {

	class MeshFactory {
	public:
		Mesh* CreateQuad(const char *path, bool shouldHaveSpec = false);

		// Should be used to draw the framebuffer's colour buffer
		Mesh* CreateScreenQuad(int colourBufferId);
	};

} }