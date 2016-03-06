#include "Context.h"


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
	renderer = std::make_unique<OGLRenderer>();
}



Context::~Context()
{
}
