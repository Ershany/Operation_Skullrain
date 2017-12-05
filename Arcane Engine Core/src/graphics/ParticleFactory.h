#pragma once

//STL Includes
#include <vector>
#include <stdlib.h>
#include <time.h>

//Operation Skullrain Headers
#include "Particle.h"
#include "../platform/OpenGL/VertexArray.h"

namespace arcane { namespace graphics {

	class ParticleFactory {
	public:
		static Particle* CreateExplosion(GLuint particleTexture, int numParticles, float displacementAmount, glm::vec3 &worldPos, bool isActive);
	};

} }