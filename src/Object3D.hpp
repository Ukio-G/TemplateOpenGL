#ifndef OBJECT3D_HPP
#define OBJECT3D_HPP

#include <GL/glew.h>
#include <glm/mat4x4.hpp>
#include "BuffersCollection.hpp"
#include "Texture.hpp"
#include "Shader.h"

class Object3D {
public:
	glm::mat4 modelMatrix = glm::mat4(1);

	Geometry geometry;

	Texture * texture = nullptr;

	Object3D(Geometry geometry) : geometry(geometry) { }

	void draw(const ShaderProgram & shaderProgram) {
		bindToDraw(shaderProgram);
		glDrawElements(GL_TRIANGLES, (GLint)geometry.vertexes_count, GL_UNSIGNED_INT, 0);
	}

	void bindToDraw(const ShaderProgram & shaderProgram) {
		bindToDraw();
		shaderProgram.use();
		shaderProgram.setMatrix4d("transform", modelMatrix);
	}

	void bindToDraw() {
		if (texture)
			texture->bind();
		glBindVertexArray(geometry.buffers.VAO);
	}

	const glm::vec3 &getTranslate() const {
		return translateVector;
	}

	void setTranslate(const glm::vec3 &translate) {
		auto id = glm::mat4(1);

		translateMatrix = glm::translate(id, translateVector);
		translateVector = translate;
	}
	const glm::vec3 &getRotate() const {
		return rotateVector;
	}

	void setRotate(const glm::vec3 &rotate) {
		rotateVector = rotate;
		auto id = glm::mat4(1);

		rotationMatrix = glm::rotate(id, glm::radians(rotateVector[0]), glm::vec3(1.0, 0.0, 0.0));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotateVector[1]), glm::vec3(0.0, 1.0, 0.0));
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotateVector[2]), glm::vec3(0.0, 0.0, 1.0));
	}

	void updateModelMatrix() {
		modelMatrix = translateMatrix * rotationMatrix;
	}

	const glm::mat4 &getRotationMatrix() const {
		return rotationMatrix;
	}

	const glm::mat4 &getTranslateMatrix() const {
		return translateMatrix;
	}

private:
	glm::vec3 rotateVector = glm::vec3(0.0);
	glm::vec3 translateVector = glm::vec3(0.0);;

	glm::mat4 rotationMatrix = glm::mat4(1.0);
	glm::mat4 translateMatrix = glm::mat4(1.0);
};

#endif
