#include "Context.h"


Context& Context::getInstance()
{
	static Context  instance; // Guaranteed to be destroyed.
	// Instantiated on first use.
	return instance;
}

shared_ptr<IVertexArray>  Context::CreateVertexArray(const vector<Vertex> & vertices, const vector<int> & indices)
{
	shared_ptr<IVertexArray> vertexArray =make_shared<OGLVertexArray>( );
	vertexArray->setVertexArray(vertices, indices);
	return 0;vertexArray;
}

void Context::createOGLContext()
{
	renderer = std::make_unique<OGLRenderer>();
}



Context::~Context()
{
}
