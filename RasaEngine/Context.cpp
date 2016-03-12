#include "Context.h"

#include "GL\glew.h"
#include <GLFW\glfw3.h>


Context& Context::getInstance()
{
	static Context  instance; // Guaranteed to be destroyed.
	// Instantiated on first use.
	return instance;
}

shared_ptr<IVertexArray>  Context::CreateVertexArray(const vector<Vertex> & vertices, const vector<int> & indices)const
{
	shared_ptr<IVertexArray> vertexArray = make_shared<OGLVertexArray>();
	vertexArray->setVertexArray(vertices, indices);
	return vertexArray;
}

shared_ptr<ITextureBuffer> Context::CreateTextureBuffer(const unsigned char* const texture, const int & width, const int & height)const
{
	shared_ptr<ITextureBuffer> textureBuffer = make_shared<OGLTextureBuffer>();
	textureBuffer->setTextureBuffer(texture, width,height);
	return textureBuffer;
}

void Context::setOGLContext()
{
#pragma region OpenGlSetup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	this->window = glfwCreateWindow(screenWidth, screenHeight, "RasaEngine", nullptr, nullptr); // Windowed
	glfwMakeContextCurrent(this->window);


	// Options
	//Disabling coursor in window
	glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Initialize GLEW to setup the OpenGL Function pointers
	glewExperimental = GL_TRUE;
	glewInit();

	// Define the viewport dimensions
	glViewport(0, 0, screenWidth, screenHeight);

	// Setup some OpenGL options
	glEnable(GL_DEPTH_TEST);
#pragma endregion
	
	
	renderer = std::make_unique<OGLRenderer>();
}



Context::~Context()
{
}
