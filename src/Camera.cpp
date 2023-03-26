#include <glm/ext/matrix_transform.hpp>
#include <iostream>
#include "Camera.hpp"
#include "EventChannel.h"
#include "MouseEvents.hpp"
#include "Window.hpp"

Camera::Camera(const glm::vec3 &pos, const glm::vec3 &rotation): position(pos), rotation(rotation), movementActive(true) {
	up = {0.0, 1.0, 0.0};
	front = {0.0, 0.0, -1.0};
	this->right = glm::cross(front, up);
	viewMatrix = glm::lookAt(position, glm::normalize(pos + front), glm::normalize(up));
}

void Camera::initMovements() {
	const float cameraSpeed = 0.05f; // adjust accordingly
	auto & eventChannel = EventChannel::getInstance();

	eventChannel.publish("NewKeyEvent", std::make_pair<int, std::function<void(Window * window)>>(GLFW_KEY_W, [&, cameraSpeed](Window * window) {
		position += cameraSpeed * front;
		viewMatrix = glm::lookAt(position, position + front, up);
	}));

	eventChannel.publish("NewKeyEvent", std::make_pair<int, std::function<void(Window * window)>>(GLFW_KEY_S, [&, cameraSpeed](Window * window) {
		position -= cameraSpeed * front;
		viewMatrix = glm::lookAt(position, position + front, up);
	}));

	eventChannel.publish("NewKeyEvent", std::make_pair<int, std::function<void(Window * window)>>(GLFW_KEY_A, [&, cameraSpeed](Window * window) {
		this->position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;
		viewMatrix = glm::lookAt(position, position + front, up);
	}));

	eventChannel.publish("NewKeyEvent", std::make_pair<int, std::function<void(Window * window)>>(GLFW_KEY_D, [&, cameraSpeed](Window * window) {
		this->position += glm::normalize(glm::cross(front, up)) * cameraSpeed;
		viewMatrix = glm::lookAt(position, position + front, up);
	}));

	eventChannel.publish("NewKeyEvent", std::make_pair<int, std::function<void(Window * window)>>(GLFW_KEY_LEFT_ALT, [&, cameraSpeed](Window * window) {
		movementActive = false;
		glfwSetInputMode(window->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	}));

	eventChannel.publish("NewKeyEvent", std::make_pair<int, std::function<void(Window * window)>>(GLFW_KEY_RIGHT_ALT, [&, cameraSpeed](Window * window) {
		movementActive = true;
//		int windowsSize[2];
//		glfwGetWindowSize(window->glfwWindow, windowsSize, windowsSize + 1);
//		glfwSetCursorPos(window->glfwWindow, (double)(windowsSize[0]/2),(double)(windowsSize[1]/2));
		glfwSetInputMode(window->glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}));

	auto mouseMoveCallback = std::function<void(double,double,double,double)>([this](double x, double y, double dx, double dy) -> void {
		if (!movementActive)
			return;

		glm::vec3 direction;
		double sens = 0.1;
		dx *= sens;
		dy *= sens;

		auto & yaw = rotation.x;
		auto & pitch = rotation.y;

		yaw   -= dx;
		pitch += dy;

		if(yaw > 89.0f)
			yaw = 89.0f - 360.f;
		if(pitch < -89.0f)
			pitch = -89.0f + 360.f;;

		direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		direction.y = sin(glm::radians(pitch));
		direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		front = glm::normalize(direction);

		viewMatrix = glm::lookAt(position, position + front, up);
	});

	eventChannel.publish("NewMouseEvent", std::make_pair<EMouseEvent, std::any>(EME_MOVE, mouseMoveCallback));
}


