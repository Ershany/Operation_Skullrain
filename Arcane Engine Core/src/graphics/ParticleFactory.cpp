#include "ParticleFactory.h"

namespace arcane { namespace graphics {

	Particle* ParticleFactory::CreateExplosion(GLuint particleTexture, int numParticles, float displacementAmount, glm::vec3 &worldPos, bool isActive) {
		std::vector<GLfloat> posVector;
		std::vector<GLfloat> normVector;
		std::vector<GLfloat> colorVector;
		posVector.reserve(numParticles * 3);
		normVector.reserve(numParticles * 3);
		colorVector.reserve(numParticles * 3);

		opengl::Buffer *posBuffer = new opengl::Buffer();
		opengl::Buffer *normBuffer = new opengl::Buffer();
		opengl::Buffer *colorBuffer = new opengl::Buffer();
		srand(time(NULL));

		for (int i = 0; i < numParticles; ++i) {
			// Generate numbers between [-displacementAmount, displacementAmount]
			float randPosX = (static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / displacementAmount))) * 2 - 1;
			float randPosY = (static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / displacementAmount))) * 2 - 1;
			float randPosZ = (static_cast<float> (rand()) / (static_cast<float> (RAND_MAX / displacementAmount))) * 2 - 1;
			posVector.emplace_back(randPosX);
			posVector.emplace_back(randPosY);
			posVector.emplace_back(randPosZ);

			// Generate numbers between [-1, 1]
			float randSpeedX = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2 - 1;
			float randSpeedY = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2 - 1;
			float randSpeedZ = (static_cast <float> (rand()) / static_cast <float> (RAND_MAX)) * 2 - 1;
			normVector.emplace_back(randSpeedX);
			normVector.emplace_back(randSpeedY);
			normVector.emplace_back(randSpeedZ);

			int choice = rand() % 3;
			if (choice == 0) {
				colorVector.emplace_back(0.84f); colorVector.emplace_back(0.1f); colorVector.emplace_back(0.1f);
			}
			else if (choice == 1) {
				colorVector.emplace_back(1.0f); colorVector.emplace_back(0.78f); colorVector.emplace_back(0.18f);
			}
			else {
				colorVector.emplace_back(0.95f); colorVector.emplace_back(0.35f); colorVector.emplace_back(0.0f);
			}
		}

		posBuffer->load(&posVector[0], numParticles * 3, 3);
		normBuffer->load(&normVector[0], numParticles * 3, 3);
		colorBuffer->load(&colorVector[0], numParticles * 3, 3);

		opengl::VertexArray *vao = new opengl::VertexArray();
		vao->addBuffer(posBuffer, 0);
		vao->addBuffer(normBuffer, 1);
		vao->addBuffer(colorBuffer, 2);

		return new Particle(vao, particleTexture, worldPos, numParticles, isActive);
	}

} }