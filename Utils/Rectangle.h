#pragma once
#include<GL/glew.h>
#include<glm.hpp>
#include<gtc/type_ptr.hpp>
#include<gtc/matrix_transform.hpp>
#include<iostream>
#include<vector>
using namespace std;
class RectangleClass
{
public:
	float width = 1;
	float height = 1;
	vector<glm::vec3> vertexArr;
	vector<glm::vec2> texCoordArr;
	GLuint texId;
	glm::vec3 position;
	glm::mat4 tMat;
	RectangleClass(float w, float h);
	void generateGeometry();
	void computeMatrix();
};

