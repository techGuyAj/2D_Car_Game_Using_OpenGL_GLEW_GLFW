#include "GameScene.h"


void GameScene::init()
{
	setDefaultStateOGLParams();
	glm::vec3 eye = glm::vec3(0, 0, 1);
	glm::vec3 center = glm::vec3(0, 0, 0);
	glm::vec3 up = glm::vec3(0, 1, 0);
	viewMat = glm::lookAt(eye, center, up);
	projectionMat = glm::ortho(-screenWidth / 2, screenWidth / 2, -screenHeight / 2, screenHeight / 2, -100.0f, 1000.0f);




	programTex     = Utility_Class::createShaderProgram("Basic_Vert_Texture.glsl", "Basic_Frag_Texture.glsl");
	posLocTex     = glGetAttribLocation(programTex, "position");
	uvLocTex      = glGetAttribLocation(programTex, "uv");
	mvpLocTex     = glGetUniformLocation(programTex, "mvp");
	colorLocTex   = glGetUniformLocation(programTex, "u_color");
	samplerLocTex = glGetUniformLocation(programTex, "sampler");


	cout << "prog " << programTex << endl;
	cout << "prog " << posLocTex << endl;
	cout << "prog " << uvLocTex << endl;
	cout << "prog " << mvpLocTex << endl;
	cout << "prog " << colorLocTex << endl;
	cout << "prog " << samplerLocTex << endl;
	
	texId_Player =Utility_Class::buildTexture_PNG("Player.png");
	texId_Road   =Utility_Class::buildTexture_PNG("Road.jpg");
	texId_Police1 = Utility_Class::buildTexture_PNG("Police_1.png");
	texId_User1 = Utility_Class::buildTexture_PNG("User_2.png");

	 texId_User3 = Utility_Class::buildTexture_PNG("User3.png");
	 texId_User4 = Utility_Class::buildTexture_PNG("User4.png");


	obstacleTextures.push_back(texId_Police1);
	obstacleTextures.push_back(texId_User1);
	obstacleTextures.push_back(texId_User3);
	obstacleTextures.push_back(texId_User4);
	cout << "created program " << program << endl;


loadGameComponents();
	

}

void GameScene::setDefaultStateOGLParams() {
	glClearColor(0, 0.15, 0, 1.0f);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void GameScene::setWidthAndHeight(float w, float h) {
	screenWidth = w;
	screenHeight = h;
}

void  GameScene::drawFrame()
{
	//move road blocks here
	if (!isGameOver)
	{

		for (int i = 0; i < RoadBlocks.size(); i++)
		{

			auto obj = RoadBlocks.at(i);
			obj->position.y -= 0.5;

			if (obj->position.y < -screenHeight)
			{
				obj->position.y = screenHeight;
			}
		}

		for (int i = 0; i < obstacles.size(); i++)
		{

			auto obj = obstacles.at(i);
			obj->position.y -= obstacleCarSpeed;

			if (obj->position.y < -screenHeight)
			{
				auto rHeight = rand() % 100;
				obj->position.y = screenHeight+ rHeight;
			}
		}
	}
	collisionDetection();

	//ends here

	render();
}

void  GameScene::render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glUseProgram(programTex);

	glEnableVertexAttribArray(posLocTex);
	glEnableVertexAttribArray(uvLocTex);

	for (int i = 0; i < RoadBlocks.size(); i++)
	{
		auto obj = RoadBlocks.at(i);
		obj->computeMatrix();
		modelMat = glm::mat4(1);
		mv = viewMat * modelMat * obj->tMat;
		mvp = projectionMat * mv;

		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
		glUniform1i(samplerLocTex, 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texId_Road);
		glUniform3f(colorLocTex, 1, 0, 1);
		glVertexAttribPointer(posLocTex, 3, GL_FLOAT, GL_FALSE, 0, obj->vertexArr.data());
		glVertexAttribPointer(uvLocTex, 2, GL_FLOAT, GL_FALSE, 0, obj->texCoordArr.data());
		glDrawArrays(GL_TRIANGLES, 0, obj->vertexArr.size());
		glBindTexture(GL_TEXTURE_2D, 0);
	}


	
	//Drawing Players here
	for (int i = 0; i < GameObjects.size(); i++)
	{
		auto obj = GameObjects.at(i);
		obj->computeMatrix();
		modelMat = glm::mat4(1);
		auto scalemat = glm::scale(glm::mat4(1), glm::vec3(0.5, 0.5, 0.5));
		mv = viewMat * modelMat * obj->tMat;
		mvp = projectionMat * mv;

		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
		glUniform1i(samplerLocTex, 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, obj->texId);
		glUniform3f(colorLocTex, 1, 1, 1);
		glVertexAttribPointer(posLocTex, 3, GL_FLOAT, GL_FALSE, 0, obj->vertexArr.data());
		glVertexAttribPointer(uvLocTex, 2, GL_FLOAT, GL_FALSE, 0, obj->texCoordArr.data());
		glDrawArrays(GL_TRIANGLES, 0, obj->vertexArr.size());
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	

	//Drawing obstavle Cars here
	for (int i = 0; i < obstacles.size(); i++)
	{
		auto obj = obstacles.at(i);
		obj->computeMatrix();
		modelMat = glm::mat4(1);
		auto scalemat = glm::scale(glm::mat4(1), glm::vec3(0.5, 0.5, 0.5));
		mv = viewMat * modelMat * obj->tMat ;
		mvp = projectionMat * mv;

		glUniformMatrix4fv(mvpLoc, 1, GL_FALSE, glm::value_ptr(mvp));
		glUniform1i(samplerLocTex, 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, obj->texId);
		glUniform3f(colorLocTex, 1, 1, 1);
		glVertexAttribPointer(posLocTex, 3, GL_FLOAT, GL_FALSE, 0, obj->vertexArr.data());
		glVertexAttribPointer(uvLocTex, 2, GL_FLOAT, GL_FALSE, 0, obj->texCoordArr.data());
		glDrawArrays(GL_TRIANGLES, 0, obj->vertexArr.size());
		glBindTexture(GL_TEXTURE_2D, 0);
	}



	

	
	
	glDisableVertexAttribArray(posLocTex);
	glDisableVertexAttribArray(uvLocTex);

}
void GameScene::leftArrowClicked()
{
	if (isGameOver)
		return;
	Player->position.x -= 10;

	if (Player->position.x - Player->width / 2 < Road->position.x - Road->width / 2)
		Player->position.x = Road->position.x - Road->width / 2+ Player->width / 2;

}
void GameScene:: RightArrowClicked()
{
	if (isGameOver)
		return;

	Player->position.x += 10;


	if (Player->position.x + Player->width / 2 > Road->position.x + Road->width / 2)
		Player->position.x = Road->position.x + Road->width / 2 - Player->width / 2;
}
void GameScene::collisionDetection()
{
	//check detection b/w player and the other cars here

	for (int i = 0; i < obstacles.size(); i++)
	{
		auto carObj = obstacles.at(i);

		auto pos = Player->position;
		auto posTwo = carObj->position;


		auto d = glm::distance(pos, posTwo);
		if (d < Player->width   )
		{

			isGameOver = true;
			GameOver();
			break;
		}

	}
	/*for (int i = 0; i < obstacles.size(); i++)
	{
		auto carObj = obstacles.at(i);
		auto l1 = Player->vertexArr.at(1);
		auto r1 = Player->vertexArr.at(5);

		auto l2 = carObj->vertexArr.at(1);
		auto r2 = carObj->vertexArr.at(5);

	bool res=	doOverlap(l1,r1,l2,r2);

	if (!res)
	{
		isGameOver = true;
		GameOver();
		break;
	}
	}*/

}
void GameScene::loadGameComponents()
{

	//Creating Players.

	Road = new RectangleClass(screenWidth / 2, screenHeight);
	Road->position = glm::vec3(0, 0, 2);

	Road->texId = texId_Road;
	RoadBlocks.push_back(Road);

	auto Road_2 = new RectangleClass(screenWidth / 2, screenHeight);
	Road_2->position = glm::vec3(0, screenHeight, 2);
	Road_2->texId = texId_Road;
	RoadBlocks.push_back(Road_2);

	Player = new RectangleClass(50, 100);
	Player->position = glm::vec3(0, -screenHeight / 2 + Player->height / 2, 0);
	Player->texId = texId_Player;
	GameObjects.push_back(Player);


	//Create other obstacles

	//for (int i = 0; i < numOfObstacleCars; i++)
	{
		{
			auto obs = new RectangleClass(50, 100);

			//x between raod width max and min
			auto x = 0;
			auto randomValue = rand() % (int)(Road->width);
			x = randomValue - Road->width / 4;
			//from center to some greater than screeen height.
			auto y = 0;
			auto randomValueY = rand() % (int)(Road->height);
			y = (0) + randomValueY;
			cout << x << " , " << y << endl;
			obs->position = glm::vec3(100, screenHeight-500, 0);


			obs->texId = texId_Police1;
			obstacles.push_back(obs);
		}


		{

			auto obs1 = new RectangleClass(50, 100);

			//x between raod width max and min
			auto x = 0;
			auto randomValue = rand() % (int)(Road->width);
			x = randomValue - Road->width / 8;
			//from center to some greater than screeen height.
			auto y = 0;
			auto randomValueY = rand() % (int)(Road->height);
			y = (0) + randomValueY;
			cout << x << " , " << y << endl;
			obs1->position = glm::vec3(-200, screenHeight/2-100, 0);

			obs1->texId = texId_User3;
			obstacles.push_back(obs1);
		}

		{
			auto obs2 = new RectangleClass(50, 100);

			//x between raod width max and min
			auto x = 0;
			auto randomValue = rand() % (int)(Road->width);
			x = randomValue - Road->width / 2;
			//from center to some greater than screeen height.
			auto y = 0;
			auto randomValueY = rand() % (int)(Road->height);
			y = (0) + randomValueY;
			cout << x << " , " << y << endl;
			obs2->position = glm::vec3(100, y, 0);

			obs2->texId = texId_User1;
			obstacles.push_back(obs2);

		}
		{

			auto obs3 = new RectangleClass(50, 100);

			//x between raod width max and min
			auto x = 0;
			auto randomValue = rand() % (int)(Road->width);
			x = randomValue - Road->width / 4;
			//from center to some greater than screeen height.
			auto y = 0;
			auto randomValueY = rand() % (int)(Road->height);
			y = (0) + randomValueY;
			cout << x << " , " << y << endl;
			obs3->position = glm::vec3(-30, screenWidth/2+500, 0);


			obs3->texId = texId_Player;
			obstacles.push_back(obs3);
		}
	}
}
void GameScene::GameOver()
{
	int counter = 1; //amount of seconds
	Sleep(1000);
	while (counter >= 1)
	{
		cout << "\rTime remaining: " << counter << flush;
		Sleep(1000);
		counter--;
	}
	isGameOver = false;
	restart();
	loadGameComponents();
}
void GameScene::restart()
{
	for (int i = 0; i < GameObjects.size(); i++)
	{
		delete(GameObjects.at(i));
	}
	for (int i = 0; i < obstacles.size(); i++)
	{
		delete(obstacles.at(i));
	}
	GameObjects.clear();
	obstacles.clear();
}
bool GameScene::doOverlap(glm::vec3 l1, glm::vec3 r1, glm::vec3 l2, glm::vec3 r2)
{

	// To check if either rectangle is actually a line
	// For example :  l1 ={-1,0}  r1={1,1}  l2={0,-1}
	// r2={0,1}

	if (l1.x == r1.x || l1.y == r1.y || l2.x == r2.x
		|| l2.y == r2.y) {
		// the line cannot have positive overlap
		return false;
	}

	// If one rectangle is on left side of other
	if (l1.x >= r2.x || l2.x >= r1.x)
		return false;

	// If one rectangle is above other
	if (l1.y >= r2.y || l2.y >= r1.y)
		return false;

	return true;
}
//void pointInsideARectangle(glm::vec3 pt,RectangleClass * rect)
//{
//	auto dist = distance(pt, rect->position);
//	i
//
//}