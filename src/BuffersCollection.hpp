#ifndef BUFFERS_COLLECTION_HPP
#define BUFFERS_COLLECTION_HPP

#include "Vertex.h"

struct BuffersCollection {
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;
};

struct Geometry {
	BuffersCollection buffers;
	const Vertex* vertex_data;
	size_t indexes_count;
	size_t vertexes_count;
};

#endif
