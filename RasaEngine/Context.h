#pragma once
#include "IVertexArray.h";
#include "IRenderer.h";
#include "ITextureBuffer.h";

#include "GL\glew.h"

class GLFWwindow;

class Context
{
public:
	//Singleton pattern methods
	static Context& getInstance();
	void operator=(Context const&) = delete;
	Context(Context const&) = delete;
	~Context();
	/*  Context data  */
	GLFWwindow* window;
	GLuint screenWidth = 1200, screenHeight = 800;
	/*  Functions  */
	void setOGLContext();
	unique_ptr <IRenderer> renderer;
	shared_ptr<IVertexArray> CreateVertexArray(const vector<Vertex> & vertices, const vector<int> & indices) const;
	shared_ptr<ITextureBuffer> CreateTextureBuffer(const unsigned char* const texture, const int& width, const int& height, TextureType type)const;
	shared_ptr<ITextureBuffer> CreateTextureBuffer(vector<const unsigned char*> & textures, const int* widths, const int* heights)const;
	shared_ptr<IFrameBuffer> CreateFrameBuffer(const int & width, const int & height)const;

private:
	Context(){};

};