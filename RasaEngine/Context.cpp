#include "Context.h"


Context& Context::getInstance()
{
	static Context  instance; // Guaranteed to be destroyed.
	// Instantiated on first use.
	return instance;
}

shared_ptr<IVertexArray>  Context::CreateVertexArray(const vector<Vertex> & vertices, const vector<int> & indices)const
{
	shared_ptr<IVertexArray> vertexArray =make_shared<OGLVertexArray>( );
	vertexArray->setVertexArray(vertices, indices);
	return vertexArray;
}

void Context::setOGLContext()
{
	renderer = std::make_unique<OGLRenderer>();
}



Context::~Context()
{
}
