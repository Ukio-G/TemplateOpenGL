#include <GL/glew.h>
#include "GeometryKeeper.h"
#include "OBJ_Loader.hpp"

void GeometryKeeper::newGeometry(const std::string & name, const std::string &objFilename) {
	// Initialize Loader
	objl::Loader Loader;

	// Load .obj File
	bool loadout = Loader.LoadFile(objFilename);

	// If so continue
	if (loadout)
	{
		// Copy data (Very bad, yea, need own obj parser)
		size_t vertexes_bytes = Loader.LoadedVertices.size() * sizeof(objl::Vertex);
		size_t indexes_bytes = Loader.LoadedIndices.size() * sizeof(unsigned int);

		vertexData[name] = std::shared_ptr<void>(malloc(vertexes_bytes), free);
		indexesData[name] = std::shared_ptr<void>(malloc(indexes_bytes), free);

		void* vertex_data = vertexData[name].get();
		void* indexes_data = indexesData[name].get();

		memcpy(vertex_data, Loader.LoadedVertices.data(), vertexes_bytes);
		memcpy(indexes_data, Loader.LoadedIndices.data(), indexes_bytes);
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
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes_bytes, indexes_data, GL_STATIC_DRAW);

		// Make VBO buffer active
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertexes_bytes, vertex_data, GL_STATIC_DRAW);

		// Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(objl::Vertex), (void*)0);
		glEnableVertexAttribArray(0);

		// Normal
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(objl::Vertex), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// Texture Coordinate
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(objl::Vertex), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// Color
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(objl::Vertex), (void*)(8 * sizeof(float)));
		glEnableVertexAttribArray(3);

		availableGeometryBuffers[name] = {{VAO, VBO, EBO}, (const Vertex*)vertex_data, Loader.LoadedVertices.size(), Loader.LoadedIndices.size()};
	}
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

	// Position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	// Normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture Coordinate
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Color
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(8 * sizeof(float)));
	glEnableVertexAttribArray(3);

	availableGeometryBuffers[name] = {{VAO, VBO, EBO}, vertexData, vertexes_count, indexes_count};
}