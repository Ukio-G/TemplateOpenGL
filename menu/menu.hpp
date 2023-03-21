#ifndef MENU_HPP
#define MENU_HPP 

#include "imgui/imgui.h"
#include "glm/glm.hpp"
#include "include/Vertex.h"
#include "src/Object3D.hpp"
#include <vector>

void translationWindow(Object3D & object);
void rotationWindow(Object3D & object);
void showMatrix(const glm::mat4 &mat, const char * matrixLabel);
void vertexW_Window(float & vertex_w);
void projectionUsage(glm::mat4 & projectionMatrix);
void vertexMatrixCalculation(Object3D & object3D, glm::mat4 &proj_matrix, const float & vertex_w);
void drawMenu(Object3D & object, glm::mat4 & projectionMatrix);

#endif