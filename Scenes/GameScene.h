
#include<GL/glew.h>
#include<glm.hpp>
#include<gtc/type_ptr.hpp>
#include<gtc/matrix_transform.hpp>
#include<iostream>
#include<vector>
#include<random>
#include <cstdlib>
#include <ctime>
#include<Rectangle.h>
#include<Utility_Class.h>
#include <Windows.h>

class GameScene
{
public:

	RectangleClass* Player;
	RectangleClass* Road;
	vector< RectangleClass*> GameObjects;
	vector< RectangleClass*> RoadBlocks;
	vector< RectangleClass*> obstacles;

	float screenWidth = 512, screenHeight = 512;
	double mouseX = 0, mouseY = 0;
	glm::mat4 viewMat, projectionMat, mvp, mv, modelMat;
	GLuint program, posLoc, colorLoc, mvpLoc;
	GLuint programTex,posLocTex,uvLocTex,mvpLocTex,colorLocTex,samplerLocTex;
	GLuint texId_Player, texId_Road, texId_User1, texId_User3, texId_User4, texId_Police1;
	vector<GLuint>obstacleTextures;
	bool isGameOver = false;

	float playerCarSpeed = 1.0f;
	float obstacleCarSpeed =0.5f;

	float numOfObstacleCars = 3;

	void init();
	void render();
	void drawFrame();
	void setDefaultStateOGLParams();
	void setMousePosition(double x, double y);
	void setWidthAndHeight(float w, float h);

	void leftArrowClicked();
	void RightArrowClicked();

	void collisionDetection();
	void restart();
	void GameOver();
	void loadGameComponents();
	bool doOverlap(glm::vec3 l1, glm::vec3 r1, glm::vec3 l2, glm::vec3 r2);
	
};

