#include "Vertex.h"

Vertex plane_vertices[] {
    {-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, -1.0f, -1.0f, 0.5f, 0.2f, 0.0f},
    {-0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,  1.0f, 0.0f, 0.3f, 0.1f},
    { 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f,  1.0f,  1.0f, 0.0f, 0.0f, 0.0f},
    { 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f,  1.0f, -1.0f, 0.5f, 0.0f, 0.5f}
};

unsigned int plane_indexes[] = {0, 1, 2, 0, 2, 3};