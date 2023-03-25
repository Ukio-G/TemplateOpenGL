#include <stdexcept>

#ifdef __APPLE__
#  include <GL/glew.h>
#  include <OpenGL/gl.h>
#  include <OpenGL/glext.h>
#else
#  include <GL/glew.h>
#endif

#include "Window.hpp"

void Window::initGLFW() {
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	settings.apply();

	// Create a GLFWwindow object that we can use for GLFW's functions
	glfwWindow = glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);

	if (glfwWindow == nullptr)
		throw std::runtime_error("Failed to create GLFW glfwWindow");

	glfwSetInputMode(glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwMakeContextCurrent(glfwWindow);
}

void Window::initIMGUI() {
	// Setup Dear ImGui context
	const char* glsl_version = "#version 150";

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
}

void Window::initGLEW() {
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
		throw std::runtime_error("Failed to initialize GLEW");
}

void Window::initViewport() {
	glViewport(0, 0, width, height);
}

Window::Window(int width, int height) : width(width), height(height), name("Window") {
	init();
}

void Window::init() {
	initGLFW();
	initGLEW();
	initViewport();
	initIMGUI();
}
