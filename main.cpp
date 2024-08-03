
#include<GL/glew.h>
#include<GL/gl.h>
#include <GLFW/glfw3.h>
#include<fstream>
#include<iostream>
#include<sstream>
#include<GameScene.h>

using namespace std;




bool leftMouseClicked = false;
int screenWidth = 1024, screenHeight = 800;

void init();
void render();
GameScene *scene;

void convertToScreenCoordinates(double& posX, double& posY)
{
    posX = posX - screenHeight / 2;
    posY = screenHeight / 2 - posY;
}
void cursor_position_Callback(GLFWwindow* window, double xPos, double yPos)
{
    if (leftMouseClicked)
    {

        convertToScreenCoordinates(xPos, yPos);
       
    }

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mode)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        if (action == GLFW_PRESS)
        {

        }
        if (action == GLFW_RELEASE)
        {

        }
    }
    if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        if (action == GLFW_PRESS)
        {
            leftMouseClicked = true;
            double xPos = 0, yPos = 0;
            glfwGetCursorPos(window, &xPos, &yPos);
           // cout << " xPos " << xPos << " yPos " << yPos << endl;

            //convert to origin at center

            float xVal = xPos - screenHeight / 2;
            float yVal = screenHeight / 2 - yPos;
           // cout << " new xPos " << xVal << " yPos " << yVal << endl;
            
        }
        if (action == GLFW_RELEASE)
        {
            leftMouseClicked = false;
        }
    }

}






void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
       
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
    {
        scene->leftArrowClicked();
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
    {
        scene->RightArrowClicked();
    }

}
int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(screenWidth, screenHeight, "Game", NULL, NULL);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    GLenum err = glewInit();
    if (err != GLEW_OK)
        std::cout << "error with GLEW initialization" << std::endl;
  //  std::cout << "opengl version " << glGetString(GL_VERSION) << std::endl;

    glfwSetCursorPosCallback(window, cursor_position_Callback);

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, key_callback);
    init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
        //glClearColor(0, 0, 0.5, 1);
        /* Swap front and back buffers */
        render();
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();



    }
    glfwTerminate();
    return 0;
}
void init()
{
    cout << screenWidth << ", " << screenHeight << endl;
    scene = new GameScene();
    scene->setWidthAndHeight(screenWidth, screenHeight);
    scene->init();
    cout << "scene initialized" << endl;
 
}
void render()
{
    	//glClearColor(0, 0.15, 0, 1.0f);
    	 scene->drawFrame();
}
