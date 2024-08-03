#include "Rectangle.h"
RectangleClass::RectangleClass(float w, float h)
{
	width = w;
	height = h;

	generateGeometry();
}
void RectangleClass::generateGeometry()
{
	//will have 2 Triangles

	//Triangle One
	glm::vec3 p1 = glm::vec3(-width / 2, -height / 2, 0);
	glm::vec3 p2 = glm::vec3(-width / 2, height / 2, 0);
	glm::vec3 p3 = glm::vec3(width / 2, height / 2, 0);

	//Triangle Two
	glm::vec3 p4 = glm::vec3(-width / 2, -height / 2, 0);
	glm::vec3 p5 = glm::vec3(width / 2, height / 2, 0);
	glm::vec3 p6 = glm::vec3(width / 2, -height / 2, 0);


	vertexArr.push_back(p1);
	vertexArr.push_back(p2);
	vertexArr.push_back(p3);
	vertexArr.push_back(p4);
	vertexArr.push_back(p5);
	vertexArr.push_back(p6);


	texCoordArr.push_back(glm::vec2(0, 0));
	texCoordArr.push_back(glm::vec2(0, 1));
	texCoordArr.push_back(glm::vec2(1, 1));

	texCoordArr.push_back(glm::vec2(0, 0));
	texCoordArr.push_back(glm::vec2(1, 1));
	texCoordArr.push_back(glm::vec2(1, 0));

	computeMatrix();

}
void RectangleClass :: computeMatrix()
{
	tMat = glm::translate(glm::mat4(1), position);
}