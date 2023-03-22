#ifndef WINDOW_HPP
#define WINDOW_HPP


// GLEW
#define GLEW_STATIC
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

//ImGui
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui.h"

#include "WindowSettings.hpp"

class Window {
public:
	Window(int width, int height);
	void initGLFW();
	void initIMGUI();
	void initGLEW();
	void initViewport();

	void init();

	int width;
	int height;
	std::string name = "Window";
	GLFWwindow* window;
	WindowSettings settings;
};

#endif