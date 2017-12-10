#include <iostream>
#include "graphics/Window.h"
#include "utils/Timer.h"
#include "graphics/Shader.h"
#include <SOIL.h>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "utils/Time.h"
#include "graphics/camera/Camera.h"
#include "utils/Logger.h"
#include "graphics/Model.h"
#include "terrain/Terrain.h"
#include "Scene3D.h"
#include "platform/OpenGL/Framebuffer.h"
#include "graphics/MeshFactory.h"



int main() {
	arcane::graphics::Window window("Arcane Engine", 1366, 768);
	arcane::Scene3D scene(&window);
	arcane::opengl::Framebuffer framebuffer(window.getWidth(), window.getHeight());
	arcane::opengl::Framebuffer blitFramebuffer(window.getWidth(), window.getHeight(), false);
	arcane::graphics::Shader framebufferShader("src/shaders/framebuffer.vert", "src/shaders/framebuffer.frag");
	arcane::graphics::MeshFactory meshFactory;
	arcane::graphics::Mesh *colourBufferMesh = meshFactory.CreateScreenQuad(blitFramebuffer.getColourBufferTexture());

	arcane::Timer fpsTimer;
	int frames = 0;

	arcane::Time deltaTime;
	while (!window.closed()) {
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		window.clear();
		deltaTime.update();

		
		if (window.isKeyPressed(GLFW_KEY_W)) {
			scene.buttonPressed(GLFW_KEY_W, deltaTime.getDeltaTime());
		}
		if (window.isKeyPressed(GLFW_KEY_S)) {
			scene.buttonPressed(GLFW_KEY_S, deltaTime.getDeltaTime());
		}
		if (window.isKeyPressed(GLFW_KEY_A)) {
			scene.buttonPressed(GLFW_KEY_A, deltaTime.getDeltaTime());
		}
		if (window.isKeyPressed(GLFW_KEY_D)) {
			scene.buttonPressed(GLFW_KEY_D, deltaTime.getDeltaTime());
		}
		if (window.isKeyPressed(GLFW_KEY_SPACE)) {
			scene.buttonPressed(GLFW_KEY_SPACE, deltaTime.getDeltaTime());
		}
		if (window.isKeyPressed(GLFW_KEY_LEFT_CONTROL)) {
			scene.buttonPressed(GLFW_KEY_LEFT_CONTROL, deltaTime.getDeltaTime());
		}
		if (window.isKeyPressed(GLFW_KEY_C)) {
			scene.buttonPressed(GLFW_KEY_C, deltaTime.getDeltaTime());
		}
		if (window.isKeyPressed(GLFW_KEY_V)) {
			scene.buttonPressed(GLFW_KEY_V, deltaTime.getDeltaTime());
		}
		if (window.isKeyPressed(GLFW_KEY_K)) {
			scene.buttonPressed(GLFW_KEY_K, deltaTime.getDeltaTime());
		}
		if (window.isKeyPressed(GLFW_KEY_1)) {
			scene.buttonPressed(GLFW_KEY_1, deltaTime.getDeltaTime());
		}
		if (window.isKeyPressed(GLFW_KEY_2)) {
			scene.buttonPressed(GLFW_KEY_2, deltaTime.getDeltaTime());
		}
		if (window.isKeyPressed(GLFW_KEY_3)) {
			scene.buttonPressed(GLFW_KEY_3, deltaTime.getDeltaTime());
		}
		
		// Draw the scene to our custom multisampled framebuffer
		framebuffer.bind();
		window.clear();
		scene.onUpdate(deltaTime.getDeltaTime());
		scene.onRender();

		// Blit the multisampled framebuffer over to a non-multisampled framebuffer
		glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer.getFramebuffer());
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, blitFramebuffer.getFramebuffer());
		glBlitFramebuffer(0, 0, window.getWidth(), window.getHeight(), 0, 0, window.getWidth(), window.getHeight(), GL_COLOR_BUFFER_BIT, GL_NEAREST);

		// Draw to the default framebuffer buffer
		framebuffer.unbind();
		window.clear();
		framebufferShader.enable();
		colourBufferMesh->Draw(framebufferShader);
		framebufferShader.disable();
		

		window.update();
		if (fpsTimer.elapsed() >= 1) {
			std::cout << "FPS: " << frames << std::endl;
			frames = 0;
			fpsTimer.reset();
		}
		else {
			frames++;
		}
	}
	return 0;
}