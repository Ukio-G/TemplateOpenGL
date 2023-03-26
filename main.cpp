#include <iostream>
#include "src/Window.hpp"
#include "src/Texture.hpp"

#include "Vertex.h"

#include "src/Shader.h"
#include "primitives/triangle.h"
#include "primitives/rectangle.h"

#include <glm/glm.hpp>
#include "menu/menu.hpp"

#include "include/math.hpp"
#include "src/GeometryKeeper.h"
#include "src/Camera.hpp"
#include "src/KeysControls.hpp"
#include "src/mouseHandler.hpp"

int main() {
	Window window(800, 800);

	// Init shaders
	Shader vs("shaders/vs.glsl", GL_VERTEX_SHADER);
	Shader fs("shaders/fs.glsl", GL_FRAGMENT_SHADER);
	ShaderProgram shaderProgram(&vs, &fs);

	auto house_texture = Texture("../textures/Cottage_Clean_Base_Color.png");
	auto texture = Texture("../texture.jpeg");

	GeometryKeeper geometryKeeper;
	geometryKeeper.newGeometry("triangle", (Vertex *) triangle_vertices, (int *) triangle_indexes, 3, 3);
	geometryKeeper.newGeometry("rectangle", (Vertex *) plane_vertices, (int *) plane_indexes, 4, 6);
	geometryKeeper.newGeometry("house", "../models/Cottage_FREE.obj");

	KeysControls keysControls(window);
	MouseControls mouseControls(window);

	Camera c({0.0f, 0.0f, 0.0f}, {-270.0f, 0.0f, 0.0f});
	c.initMovements();

	Object3D house = geometryKeeper.instanceObject3D("house");
	Object3D rectangle = geometryKeeper.instanceObject3D("rectangle");

	rectangle.setTranslate({0.0, 0.0, 5.0});
	house.setTranslate({0.0, 0.0, 30.0});
	house.updateModelMatrix();
	rectangle.updateModelMatrix();

	rectangle.texture = &texture;
	house.texture = &house_texture;

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window.glfwWindow)) {
		glm::mat4 projectionMatrix = glm::mat4(1.0f);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		/* ImGui::ShowDemoWindow(&show_demo_window); */

		drawMenu(rectangle, projectionMatrix, c);
		ImGui::Render();

		keysControls.pollingKeysEvent();
		mouseControls.pollingMouseEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.setMatrix4d("projection", projectionMatrix);
		shaderProgram.setMatrix4d("view", c.viewMatrix);
		rectangle.draw(shaderProgram);
		house.draw(shaderProgram);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the screen buffers
		glfwSwapBuffers(window.glfwWindow);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}
