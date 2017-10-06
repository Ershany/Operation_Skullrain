#pragma once

#include <string>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <SOIL.h>
#include <iostream>
#include <stb_image_aug.h>
#include <vector>
#include "../../utils/Logger.h"

namespace arcane { namespace opengl {

	class Utility {
	public:
		// isSRGB should be true for any textures that explicitly define colours for objects. This will make all of the colour values linear which is what we need in order to model lighting in the real world
		// At the end of all of the rendering passes, colour correction will be applied
		static GLuint loadTextureFromFile(const char *path, bool containsTransparencyOnSides = false, bool isSRGB = false);

		static GLuint loadCubemapFromFiles(const std::vector<const char*> &vec);
	};

} }