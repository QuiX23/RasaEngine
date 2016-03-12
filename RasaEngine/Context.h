#pragma once
#include <iostream>
#include <cstdlib>
#include <windows.h>

#include "OGLRenderer.h"
#include "OGLVertexArray.h"

#include "GL\glew.h"
#include <GLFW\glfw3.h>

class Context
{
public:
	//Singleton pattern methods
	static Context& getInstance();
	void operator=(Context const&) = delete;
	Context(Context const&) = delete;
	~Context();
	GLFWwindow* window;

	GLuint screenWidth = 800, screenHeight = 600;

	void setOGLContext();
	unique_ptr <IRenderer> renderer;
	shared_ptr<IVertexArray> CreateVertexArray(const vector<Vertex> & vertices, const vector<int> & indices) const;
	shared_ptr<ITextureBuffer> CreateTextureBuffer(const unsigned char* const texture, const int & width, const int & height)const;

private:
	Context(){};

};