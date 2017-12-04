#pragma once

//Dependancies
#include "../../Dependancies.h"

//STL Includes
#include <string>
#include <iostream>
#include <vector>

//Operation Skullrain Headers
#include "../../utils/Logger.h"
#include "../../Defs.h"

namespace arcane { namespace opengl {

	class Utility {
	public:
		static GLuint loadTextureFromFile(const char *path, bool containsTransparencyOnSides = false);
		static GLuint loadCubemapFromFiles(const std::vector<const char*> &vec);
	};

} }