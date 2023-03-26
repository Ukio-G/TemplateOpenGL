#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include "Window.hpp"

class Camera {
public:
	Camera(const glm::vec3 & pos, const glm::vec3 &rotation);
	void initMovements();

	glm::vec3 position;
	glm::vec3 rotation;

	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;

	glm::mat4 viewMatrix;
	bool movementActive;
};
#endif
