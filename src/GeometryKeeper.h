#ifndef GEOMETRY_KEEPER_HPP
#define GEOMETRY_KEEPER_HPP

#include <tuple>
#include <GL/gl.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <stdexcept>
#include "Vertex.h"
#include "Object3D.hpp"
#include "BuffersCollection.hpp"

class GeometryKeeper {
public:
	std::unordered_map<std::string, Geometry> availableGeometryBuffers;

	void newGeometry(const std::string & objFilename);
	void newGeometry(const std::string &name, const Vertex *vertexData, const int *indexes, size_t vertexes_count,
					size_t indexes_count);
	void newGeometry(const std::string &name, const std::vector<Vertex> &data, const std::vector<int> &indexes);

	Object3D instanceObject3D(const std::string & name) {
		if (availableGeometryBuffers.find(name) != availableGeometryBuffers.end()) {
			auto result = Object3D(availableGeometryBuffers[name]);
			return result;
		}
		throw std::runtime_error("No available geometry: " + name);
	}


};


#endif
