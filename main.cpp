#include <iostream>
#include "src/Window.hpp"
#include "src/Texture.hpp"

#include "Vertex.h"

#include "src/Shader.h"
#include "primitives/triangle.h"

#include <glm/glm.hpp>
#include "menu/menu.hpp"

#include "include/math.hpp"
#include "src/GeometryKeeper.h"

// The MAIN function, from here we start the application and run the game loop
int main() {
	// Create a GLFWwindow object that we can use for GLFW's functions
	Window window(800, 800);

	// Init shaders
	Shader vs("shaders/vs.glsl", GL_VERTEX_SHADER);
	Shader fs("shaders/fs.glsl", GL_FRAGMENT_SHADER);
	ShaderProgram shaderProgram(&vs, &fs);

	auto texture = Texture("../texture.jpeg");

	GeometryKeeper geometryKeeper;
	geometryKeeper.newGeometry("triangle", (Vertex *) triangle_vertices, (int *) triangle_indexes, 3, 3);

	Object3D triangle = geometryKeeper.instanceObject3D("triangle");
	triangle.texture = &texture;

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window.window)) {
		glm::mat4 projectionMatrix = glm::mat4(1.0f);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/* ImGui::ShowDemoWindow(&show_demo_window); */

		drawMenu(triangle, projectionMatrix);
		ImGui::Render();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.setInt("texture1", 0);
		shaderProgram.setMatrix4d("projection", projectionMatrix);

		triangle.updateModelMatrix();
		triangle.draw(shaderProgram);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the screen buffers
		glfwSwapBuffers(window.window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}
