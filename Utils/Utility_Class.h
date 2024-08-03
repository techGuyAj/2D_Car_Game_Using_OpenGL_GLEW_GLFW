#pragma once
#include<GL/glew.h>
#include<iostream>
#include<string>
#include<sstream>
#include<fstream>
#include<stb_image.h>
using namespace std;
class Utility_Class
{
public:
	struct shaderProgramSource {
		string VertexShader;
		string FragmentShader;
	};
	static GLuint  createShaderProgram(string vertexShader, string fragmentShader);
	static GLuint  compileShader(string ShaderSource,GLuint type);
	static string readFromFile(string filePath);
	static shaderProgramSource parseShader(string filePath);
	static GLuint  buildTexture_PNG(string filePath);
};

