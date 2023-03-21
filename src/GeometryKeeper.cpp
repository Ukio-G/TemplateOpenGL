#include <GL/glew.h>
#include "GeometryKeeper.h"

void GeometryKeeper::newGeometry(const std::string &objFilename) {

}

void GeometryKeeper::newGeometry(const std::string & name, const std::vector<Vertex> &data, const std::vector<int> &indexes) {
	newGeometry(name, data.data(), indexes.data(), data.size(), indexes.size());
}

void GeometryKeeper::newGeometry(const std::string & name, const Vertex *vertexData, const int *indexes, size_t vertexes_count, size_t indexes_count) {
	// Generate Vertex Array Object
	unsigned int VAO;

	// Create VAO
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Generate Vertex Buffers
	unsigned int VBO, EBO;

	// Create VBO buffer
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(decltype(indexes)) * indexes_count, indexes, GL_STATIC_DRAW);

	// Make VBO buffer active
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexes_count, vertexData, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	availableGeometryBuffers[name] = {{VAO, VBO, EBO}, vertexData, vertexes_count, indexes_count};
}
